/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tools_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:57:48 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/08 11:22:45 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_single_quote_part_three(char **str, int *i, int nb_quote, char **tmp)
{
	while (str[0][*i] && str[0][*i] != 39)
		(*i)++;
	*i += nb_quote;
	*tmp = ft_substr(*str, 0, *i);
	if (!*tmp)
		return (-1);
	return (1);
}

int	skip_single_quote_part_two(char **str, char **end, int *i, int *len_str)
{
	char	*tmp;
	char	*tmp2;
	int		nb_quote;

	nb_quote = 0;
	if (!str || !str[0] || !end || !*end)
		return (-1);
	while (str[0][*i] == 39)
	{
		nb_quote++;
		(*i)++;
	}
	if (skip_single_quote_part_three(str, i, nb_quote, &tmp) == -1)
		return (-1);
	tmp2 = ft_strjoin(*end, tmp);
	free(*end);
	free(tmp);
	if (!*tmp2)
		return (-1);
	*end = tmp2;
	*str += *i;
	*len_str -= *i;
	*i = -1;
	return (0);
}
/*
 ** Need to add number of single or double quote to *i
 ** like this we can skip """A""" """*i = *i + quote
 */

void	skip_no_dollar(char **str, int *i, int *nb_single, int *nb_double)
{
	int	nb_dollar;
	int	j;

	nb_dollar = 0;
	j = *i;
	if (str[0][j] != 39 && str[0][j] != 34)
	{
		while (str[0][j] && (str[0][j] != 39
					&& str[0][j] != 34 /*&& str[0][*i] != '$'*/))
		{
			if (str[0][j] == '$')
				nb_dollar++;
			j++;
		}
		if (nb_dollar == 0)
		{
			*i = j + *nb_single;
			*i = j + *nb_double;
			if (*nb_double > 0 && *nb_single == 0)
				(*i)--;
		}
	}
}
/*
   Count number of ' or ", need to know if we skip the expand value or not
 */

void	skip_single_quote_part_one(char **str, int *i,
		int *nb_single_quote, int *nb_double_quote)
{
	if (!str || !str[0])
		return ;
	*nb_single_quote = 0;
	*nb_double_quote = 0;
	skip_find_quote(str, i, nb_single_quote, nb_double_quote);
	if (str[0][*i] && str[0][*i] != '$'
			&& (*nb_single_quote > 0 || *nb_double_quote > 0))
	{
		skip_no_dollar(str, i, nb_single_quote, nb_double_quote);
	}
}

int	go_to_dollar(char **str, char **end, int *len_str, int *i)
{
	int	nb_single_quote;
	int	nb_double_quote;

	nb_single_quote = 0;
	nb_double_quote = 0;
	if (!str || !end)
		return (0);
	while (*len_str > *i && str[0][*i] && str[0][*i] != '$')
	{
		skip_single_quote_part_one(str, i, &nb_single_quote, &nb_double_quote);
		if (nb_single_quote > 0 && nb_double_quote == 0)
		{
			if (skip_single_quote_part_two(str, end, i, len_str) < 0)
				return (-1);
		}
		if (*i > *len_str || (*i >= 0 && *str && str[0][*i] == '$'))
			break ;
		if (*str)
			(*i)++;
	}
	return (nb_single_quote + nb_double_quote);
}
