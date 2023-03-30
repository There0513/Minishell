/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:55:33 by threiss           #+#    #+#             */
/*   Updated: 2022/02/08 20:00:08 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_in_word(char **str, int *i, int *in_word, int *sec_quote_found)
{
	if (!str)
		return (0);
	if ((*in_word == INSIDE_DOUBLE && (*str)[*i] == 34)
		|| (*in_word == INSIDE_SINGLE && (*str)[*i] == 39))
	{
		*sec_quote_found = 1;
		if ((*str)[*i] == 34)
			*in_word = INSIDE_DOUBLE;
		else if ((*str)[*i] == 39)
			*in_word = INSIDE_SINGLE;
		if ((*str)[*i])
			(*i)++;
		if (((*str)[*i] == '<' || (*str)[*i] == '>' || (*str)[*i] == '|')
			|| (*str)[*i] == ' ')
		{
			*sec_quote_found = 1;
			return (0);
		}
		*in_word = 0;
	}
	return (1);
}

int	check_out_word(char **str, int *i, int *in_word, int *sec_quote_found)
{
	if (!str)
		return (0);
	if (*in_word == 0 && (*str)[*i] == 34)
	{
		*in_word = INSIDE_DOUBLE;
		*sec_quote_found = 0;
	}
	else if (*in_word == 0 && (*str)[*i] == 39)
	{
		*in_word = INSIDE_SINGLE;
		*sec_quote_found = 0;
	}
	if (*in_word == 0 && *sec_quote_found == 0
		&& (((*str)[*i] == '<' || (*str)[*i] == '>' || (*str)[*i] == '|')
		|| (*str)[*i] == ' '))
	{
		return (0);
	}
	return (1);
}

int	check_add_word_two(int sec_quote_found, int in_word, t_token **token)
{
	if (!token)
		return (1);
	if (sec_quote_found != 1 && in_word != 0)
	{
		free(*token);
		printf("quote not closed.\n");
		return (1);
	}
	return (0);
}

int	check_add_word(char **str, t_list **word_lst)
{
	t_token	*token;
	int		i;
	int		sec_quote_found;
	int		in_word;

	i = 0;
	sec_quote_found = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		return (-1);
	in_word = 0;
	check_loop_word(str, &i, &in_word, &sec_quote_found);
	if (check_add_word_two(sec_quote_found, in_word, &token))
		return (-2);
	token->str = ft_substr(*str, 0, i);
	if (!token->str)
	{
		free(token);
		return (-1);
	}
	if (!add_elem_in_word(word_lst, &token))
		return (-1);
	*str += i;
	return (0);
}

int	create_token_lst(t_list **word_lst, char **str)
{
	int	result;

	result = -1;
	if (!str || !*str || !word_lst)
		return (-1);
	while (**str)
	{
		while (ft_isspace(**str))
			(*str)++;
		if (str && *str)
			result = check_add_special_signs(str, word_lst);
		if (result == -1)
			return (-1);
		if (str && *str && result == 1)
			(*str)++;
		else
		{
			result = check_add_word(str, word_lst);
			if (result == -1)
				return (-1);
			if (result == -2)
				return (-2);
		}
	}
	return (0);
}
