/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:51:53 by threiss           #+#    #+#             */
/*   Updated: 2022/02/16 16:22:16 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_file(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		printf("\t'%s' is file or folder\n", str);
		return (1);
	}
	else
		return (0);
	return (0);
}

int	check_add_simple_cmd_two(t_action **action, char **split, char *tmp_cmd,
		int *i)
{
	if (!loop_tmp_cmd(action, split, &tmp_cmd, i))
	{
		if (tmp_cmd)
			free(tmp_cmd);
		return (0);
	}
	(*action)->cmd = ft_split_parser(tmp_cmd, ' ');
	if (!(*action)->cmd)
	{
		free(tmp_cmd);
		return (0);
	}
	free(tmp_cmd);
	return (1);
}

/* NEED TO HANDLE THIS PART PROPERLY
** added:   "tmp = ft_strjoin(tmp_cmd, " ");
**          free(tmp_cmd);
**          tmp_cmd = ft_strjoin(tmp, split[i]);
**          free(tmp);"
** tmp for testing code ('ls -la | grep srcs' working with this)
*/
int	check_add_simple_cmd(char **split, t_action **action)
{
	char	*tmp_cmd;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!split[0])
		return (0);
	if (split[0][0])
		tmp_cmd = ft_strdup(split[0]);
	if (split[i] && split[i][0] == '-' && split[i][1] == 'n')
		if (check_echo_option(split[i], &tmp_cmd) == 1)
			i++;
	if (check_add_simple_cmd_two(action, split, tmp_cmd, &i) != 1)
		return (0);
	simple_parse_cmd(action);
	return (1);
}
