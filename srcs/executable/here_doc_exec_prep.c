/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exec_prep.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:36:38 by threiss           #+#    #+#             */
/*   Updated: 2022/02/07 19:05:19 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    • Support « and » when the first parameter is "here_doc"
    $> ./pipex here_doc LIMITER cmd cmd1 file
    Must be equivalent to:
    cmd << LIMITER | cmd1 >> file
*/
int	gnl_next(int fd, char **line, char *limiter, t_list **envp_lst)
{
	char	*new_line;

	new_line = NULL;
	if (ft_strncmp(*line, limiter, ft_strlen(limiter)) == 0
		&& ft_strlen(limiter) == (ft_strlen(*line) - 1))
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	new_line = find_dollar(*line, envp_lst);
	free(*line);
	*line = NULL;
	if (!new_line)
		return (0);
	write(fd, new_line, ft_strlen(new_line));
	free(new_line);
	return (1);
}

int	get_next_line(char **line)
{
	char	*input;
	char	buf;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!line)
		return (-1);
	input = malloc(sizeof(char) * 9450);
	if (!input)
		return (-1);
	ret = read(0, &buf, 1);
	while (ret > 0 && buf != '\n' && buf != '\0')
	{
		input[i] = buf;
		i++;
		ret = read(0, &buf, 1);
	}
	if (i > 0)
		input[i] = '\n';
	input[++i] = '\0';
	*line = input;
	return (ret);
}
