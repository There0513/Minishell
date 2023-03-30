/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:34:34 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/10 18:46:24 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_redirection_one(const char *pipe, int *i)
{
	if ((pipe[*i + 1] && pipe[*i + 1] == '>'
			&& pipe[*i + 2] && pipe[*i + 2] == '>')
		|| (pipe[*i + 1] && pipe[*i + 1] == '<'
			&& pipe[*i + 2] && pipe[*i + 2] == '<')
		|| (pipe[*i] == '>' && pipe[*i + 1] == '<')
		|| (pipe[*i] == '<' && pipe[*i + 1] == '>'))
	{
		return (0);
	}
	return (1);
}

int	check_redirection_two(const char *pipe, int *j)
{
	while (pipe[*j])
	{
		if (pipe[*j] == '>' || pipe[*j] == '<'
			|| pipe[*j] == '|')
		{
			return (0);
		}
		else if (pipe[*j] >= 1 && pipe[*j] <= 126 && pipe[*j] != ' ')
		{
			break ;
		}
		(*j)++;
	}
	return (1);
}

void	open_path(t_redir **redir, const char *tmp)
{
	if (!redir || !*redir | !tmp)
		return ;
	if (((*redir)->type_one == '>' && (*redir)->type_two == 0)
		|| ((*redir)->type_one == '<' && (*redir)->type_two == '<'))
		(*redir)->fd
			= open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if ((*redir)->type_one == '<'
		&& (*redir)->type_two == 0)
		(*redir)->fd = open(tmp, O_RDONLY, 0666);
	else if ((*redir)->type_one == '>'
		&& (*redir)->type_two == '>')
		(*redir)->fd
			= open(tmp, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if ((*redir)->type_one == '<'
		&& (*redir)->type_two == '<')
		(*redir)->fd = open(tmp, O_RDONLY, 0666);
}

int	loop_quotes_two(const char *str, int *j, int *in, int *save_quote)
{
	if (*in == REDIR_OUT)
	{
		*save_quote = *j;
		*in = REDIR_IN;
	}
	else
	{
		if (str && str[*save_quote] != str[*j])
		{
			*in = REDIR_IN;
			(*j)--;
			if (*j < 0)
				*j = 0;
			return (1);
		}
		else
			*in = REDIR_OUT;
	}
	(*j)--;
	return (0);
}

int	loop_quotes(const char *str)
{
	int	j;
	int	in;
	int	save_quote;

	j = 0;
	in = REDIR_OUT;
	save_quote = 0;
	if (str && (str[0] == 34 || str[0] == 39))
		in = REDIR_IN;
	if (str && (str[j] == 34 || str[j] == 39))
	{
		while (str[j] && in == REDIR_IN)
		{
			if (loop_quotes_two(str, &j, &in, &save_quote))
				return (j);
			j++;
		}
	}
	if (j < 0)
		j = 0;
	return (j);
}
