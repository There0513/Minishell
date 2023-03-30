/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:50:14 by threiss           #+#    #+#             */
/*   Updated: 2022/02/01 15:56:09 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	check_redirection_error(t_list **lst)
{
	t_token	*token;
	t_token	*token_next;

	token = NULL;
	token_next = NULL;
	if (!lst)
		return (0);
	while (*lst)
	{
		token = (*lst)->content;
		if ((*lst)->next)
		{
			token_next = (*lst)->next->content;
			if (token->str && token_next->str
				&& (token->str[0] == '>' || token->str[0] == '<')
				&& (token_next->str[0] == '>' || token_next->str[0] == '<'))
				return (0);
		}
		if ((token->str[0] == '>' || token->str[0] == '<')
			&& (*lst)->next == NULL)
			return (0);
		lst = &(*lst)->next;
	}
	return (1);
}

int	check_pipe_error(t_list **lst)
{
	t_token	*token;
	t_token	*token_next;

	token = NULL;
	token_next = NULL;
	if (!lst)
		return (0);
	while (*lst)
	{
		token = (*lst)->content;
		if ((*lst)->next)
		{
			token_next = (*lst)->next->content;
			if (token->str && token_next->str && token->str[0] == '|'
				&& token_next->str[0] == '|')
				return (0);
		}
		if ((token->str[0] == '|')
			&& (*lst)->next == NULL)
			return (0);
		lst = &(*lst)->next;
	}
	return (1);
}

int	error_check(t_list **word_lst, char *str)
{
	int	result;

	result = create_token_lst(word_lst, &str);
	if (result == -1)
		return (-1);
	if (result == -2)
		return (-2);
	if (!check_redirection_error(word_lst))
	{
		write(2, "Redirection unexpected\n", 23);
		return (-2);
	}
	if (!check_pipe_error(word_lst))
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		return (-2);
	}
	return (1);
}
