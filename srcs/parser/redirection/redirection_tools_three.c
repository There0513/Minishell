/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools_three.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:44:20 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/17 11:54:58 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_redir_part_three(t_redir **redir, const char *pipe, int *i, int *j)
{
	if (!redir || !*redir)
	{
		if (redir && *redir)
			free(*redir);
		return (0);
	}
	*j = get_path(redir, pipe, *j, *j);
	if (*j < 0)
	{
		free(*redir);
		return (-1);
	}
	else if (*j == 0)
		return (0);
	if (!pipe[*j])
		*i = *j;
	else
		*i += *j - *i;
	while (pipe[*i] && (pipe[*i] == '>' || pipe[*i] == '<'))
		(*i)--;
	return (1);
}

int	check_redir_part_two(t_redir **redir, const char *pipe, int *i, int *j)
{
	int	ret;

	ret = 0;
	if (!redir || !*redir)
	{
		if (redir && *redir)
			free(*redir);
		return (0);
	}
	if (!check_redirection_two(pipe, j))
	{
		free(*redir);
		return (0);
	}
	if (!pipe[*j])
	{
		free(*redir);
		return (0);
	}
	if (pipe[*i])
		ret = check_redir_part_three(redir, pipe, i, j);
	if (ret <= 0)
		return (ret);
	return (1);
}
