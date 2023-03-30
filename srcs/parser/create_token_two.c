/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:15:07 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/08 20:02:01 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	add_elem_in_word(t_list **word_lst, t_token **token)
{
	t_list	*elem;

	if (!word_lst || !token)
		return (0);
	if ((*token)->str == NULL)
	{
		free(*token);
		*token = NULL;
		return (0);
	}
	elem = ft_lstnew(*token);
	if (!elem)
	{
		free((*token)->str);
		free(*token);
		token = NULL;
		return (0);
	}
	if (elem)
		ft_lstadd_back(word_lst, elem);
	return (1);
}

char	*add_red_left(char **str)
{
	if (!str)
		return (NULL);
	if (*(*(str) + 1) == '<')
	{
		(*str) += 1;
		return (ft_strdup("<<"));
	}
	else
	{
		return (ft_strdup("<"));
	}
	return (NULL);
}

char	*add_red_right(char **str)
{
	if (!str)
		return (NULL);
	if (*(*(str) + 1) == '>')
	{
		(*str) += 1;
		return (ft_strdup(">>"));
	}
	else
	{
		return (ft_strdup(">"));
	}
	return (NULL);
}

int	check_add_special_signs(char **str, t_list **word_lst)
{
	t_token	*token;

	if (!str || !word_lst)
		return (-1);
	token = malloc(sizeof(t_token));
	if (!token)
		return (-1);
	if (**str == '|')
		token->str = ft_strdup("|");
	else if (**str == '<')
		token->str = add_red_left(str);
	else if (**str == '>')
		token->str = add_red_right(str);
	else
	{
		free(token);
		return (0);
	}
	if (!add_elem_in_word(word_lst, &token))
	{
		free(token->str);
		free(token);
		return (-1);
	}
	return (1);
}

void	check_loop_word(char **str, int *i, int *in_word, int *sec_quote_found)
{
	if (!str)
		return ;
	while ((*str)[*i] && (!ft_isspace((*str)[*i])
		|| (*in_word != 0 && *sec_quote_found == 0)))
	{
		if (*in_word != 0 && ((*str)[*i] == 34 || (*str)[*i] == 39))
		{
			if (!check_in_word(str, i, in_word, sec_quote_found))
				break ;
		}
		if (!check_out_word(str, i, in_word, sec_quote_found))
			break ;
		if ((*str)[*i])
			(*i)++;
	}
}
