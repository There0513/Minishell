/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tools_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:06:48 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/10 18:21:43 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit(char *tmp, char c, int *i)
{
	char	*expand;

	expand = NULL;
	if (!tmp && c == '?')
	{
		expand = ft_itoa(g_error);
		if (!expand)
			return (NULL);
		(*i)++;
	}
	return (expand);
}

void	skip_find_quote(char **str, int *i,
	int *nb_single_quote, int *nb_double_quote)
{
	if (!str || !str[0])
		return ;
	while (str[0][*i] && (str[0][*i] == 39 || str[0][*i] == 34))
	{
		if (str[0][*i] == 39)
		{
			(*nb_single_quote)++;
			if (*nb_double_quote == 0)
				break ;
		}
		else if (str[0][*i] == 34)
			(*nb_double_quote)++;
		(*i)++;
	}
}

/*
	need to add last quotes in **end
	ex : ""$USER""
	if we don't do this, *end will be ""value and not ""value""
	because find_dollar_three does not handle it
*/

int	add_quotes_in_end(char **str, char **end, int i, int addition_quote)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	i = 0;
	if ((*str)[i] == 34 || (*str)[i] == 39)
	{
		tmp = ft_substr(*str, 0, addition_quote);
		if (!tmp)
			return (i);
		tmp2 = ft_strjoin(*end, tmp);
		free(tmp);
		free(*end);
		*end = NULL;
		if (!tmp2)
			return (i);
		*end = tmp2;
		*str += addition_quote;
	}
	return (i);
}

/*
 usefull to handle $$d or more
 while (in line 105)//&& str[cpy_i - 1] == '$')
*/

int	handle_multiple_dollar(char **tmp, char *str, int *i)
{
	int	start_skip_quote;
	int	cpy_i;
	int	nb_dollar;

	if (!tmp)
		return (0);
	start_skip_quote = *i;
	cpy_i = *i;
	nb_dollar = 0;
	while (cpy_i >= 0 && str[cpy_i] && str[cpy_i] == '$')
	{
		cpy_i++;
		nb_dollar++;
	}
	if (!tmp[0] && nb_dollar > 0)
	{
		while (str[*i] && str[*i] == '$')
			(*i)++;
		while (ft_isprint(str[*i]) && str[*i] != 34 && str[*i] != 39)
			(*i)++;
		tmp[0] = ft_substr(str, start_skip_quote, *i - start_skip_quote);
		if (!tmp[0])
			return (0);
	}
	return (1);
}

/* handling things like $$value... not asked by subject, should it? */
char	*find_dollar_four(t_list **envp_lst, char *str, char *value, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (!envp_lst || !str)
		return (NULL);
	*i = expand_environment(envp_lst, str, &tmp);
	if (str[*i] && str[*i] == '?' && *i > 0 && str[*i - 1] == '$')
		tmp = expand_exit(tmp, str[*i], i);
	if (*i > 0 && str[*i - 1] == '$')
	{
		while (*i > 0 && str[*i - 1] == '$')
			(*i)--;
	}
	if (!handle_multiple_dollar(&tmp, str, i))
	{
		free(value);
		return (NULL);
	}
	return (tmp);
}
