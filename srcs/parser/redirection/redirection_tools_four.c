/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools_four.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:36:18 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 11:17:53 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_redir(t_redir **redir, const char *pipe, int *i)
{
	if (!redir || !*redir)
		return (-1);
	if (!check_redirection_one(pipe, i))
	{
		free(redir);
		return (-1);
	}
	(*redir)->fd = 0;
	(*redir)->type_one = pipe[*i];
	(*redir)->type_two = 0;
	(*redir)->here_doc_limiter = 0;
	(*redir)->fd_heredoc = 0;
	(*redir)->filename = 0;
	(*redir)->sign = 0;
	return (1);
}

int	check_add_three(t_redir **redir, const char *pipe,
	t_save_free **save_free, int *i)
{
	int	ret;

	ret = add_here_doc(redir, pipe, save_free, i);
	if (ret == -1)
		return (0);
	else if (ret == -2)
	{
		(*redir)->sign = -1;
		return (1);
	}
	return (1);
}

int	check_add_two(t_redir **redir, const char *pipe,
	t_save_free **save_free, int *i)
{
	int	ret;
	int	j;

	j = *i + 1;
	ret = 0;
	if (!redir || !save_free)
		return (0);
	if ((*redir)->type_one == '<' && (*redir)->type_two == '<')
	{
		return (check_add_three(redir, &pipe[j], save_free, i));
	}
	else
	{
		ret = check_redir_part_two(redir, pipe, i, &j);
		if (ret == -1)
			return (0);
		if (ret == 0)
		{
			(*redir)->sign = -1;
			return (1);
		}
	}
	return (1);
}
