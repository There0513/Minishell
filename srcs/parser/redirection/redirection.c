/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:46:34 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/17 11:15:15 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_read_path(const char *pipe, int i)
{
	int	sec_quote_found;
	int	in_word;

	sec_quote_found = 0;
	in_word = 0;
	while (pipe[i] && (!ft_isspace(pipe[i])
			|| (in_word != 0 && sec_quote_found == 0)))
	{
		if (in_word != 0 && (pipe[i] == 34 || pipe[i] == 39))
			if (!ft_read_inside(pipe, &i, &in_word, &sec_quote_found))
				break ;
		if (!ft_read_outside(pipe, i, &in_word, &sec_quote_found))
			break ;
		if (pipe[i])
			i++;
	}
	return (i);
}

char	*looping_way(const char *str, int *j)
{
	char	*new;
	char	*tmp;

	if (!str)
		return (NULL);
	new = ft_strdup("");
	if (!new)
		return (NULL);
	while (str[*j])
	{
		tmp = inside_loop(str, new, j);
		if (new)
			free(new);
		new = tmp;
		if (*j > 0)
			if (str[*j - 1] == '<' || str[*j - 1] == '>')
				return (new);
	}
	return (new);
}

char	*remove_start_end_quote(const char *str)
{
	char	*new;
	int		k;

	k = 0;
	k += loop_quotes(str);
	new = NULL;
	new = looping_way(str, &k);
	if (!new)
		return (NULL);
	if (new && new[0] == '\0')
	{
		free(new);
		new = NULL;
	}
	return (new);
}

/*
	opened file will be closed in prepare_redirection
	after dup2(reidr->fd, stdin/stdout)
	IF FD -1, NEED TO CLOSE ALL FD ON ERROR
	ANYWAY, WE SHOULD CLOSE ALL FD AT THE END OF THE PROGRAM
*/

int	get_path(t_redir **redir, const char *pipe, int i, int j)
{
	char	*str;
	char	*tmp;

	(*redir)->filename = NULL;
	str = NULL;
	if (!redir || !*redir)
		return (-1);
	j = ft_read_path(pipe, j);
	str = ft_substr(pipe, i, j - i);
	if (!str)
		return (-1);
	tmp = remove_start_end_quote(str);
	free(str);
	if (tmp)
		open_path(redir, tmp);
	(*redir)->filename = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	if ((*redir)->fd < 0)
	{
		g_error = 1;
		perror((*redir)->filename);
		return (0);
	}
	return (j);
}

t_redir	*check_add_redirections(const char *pipe, int *i,
	t_list **envp_lst, t_save_free **save_free)
{
	t_redir	*redir;

	if (!save_free || !*save_free)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (init_redir(&redir, pipe, i) != 1)
		return (NULL);
	if (pipe[*i + 1] == '>' || pipe[*i + 1] == '<')
	{
		redir->type_two = pipe[*i + 1];
		if (pipe[*i + 1])
			(*i)++;
	}
	(*save_free)->envp_lst = *envp_lst;
	if (!check_add_two(&redir, pipe, save_free, i))
		return (NULL);
	return (redir);
}
