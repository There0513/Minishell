/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:37:12 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/09 10:13:15 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_read_outside(const char *pipe, int i,
		int *in_word, int *sec_quote_found)
{
	if (*in_word == 0 && pipe[i] == 34)
	{
		*sec_quote_found = 0;
		*in_word = INSIDE_DOUBLE;
	}
	else if (*in_word == 0 && pipe[i] == 39)
	{
		*sec_quote_found = 0;
		*in_word = INSIDE_SINGLE;
	}
	if (*in_word == 0 && *sec_quote_found == 0
		&& ((pipe[i] == '<' || pipe[i] == '>' || pipe[i] == '|')
			|| pipe[i] == ' '))
	{
		return (0);
	}
	return (1);
}

int	ft_read_inside(const char *pipe, int *i,
		int *in_word, int *sec_quote_found)
{
	if ((*in_word == INSIDE_DOUBLE && pipe[*i] == 34)
		|| (*in_word == INSIDE_SINGLE && pipe[*i] == 39))
	{
		*sec_quote_found = 0;
		if (pipe[*i] == 34)
			*in_word = INSIDE_DOUBLE;
		else if (pipe[*i] == 39)
			*in_word = INSIDE_SINGLE;
		if (pipe[*i])
			(*i)++;
		if ((pipe[*i] == '<' || pipe[*i] == '>' || pipe[*i] == '|')
			|| pipe[*i] == ' ')
		{
			*sec_quote_found = 1;
			return (0);
		}
		*in_word = 0;
	}
	return (1);
}

char	*loop_remove_quote(const char *str, char *new, int *j)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp2 = NULL;
	i = *j;
	(*j)++;
	if (str[*j])
	{
		while (str[*j] && str[*j] != str[i])
			(*j)++;
		tmp = ft_substr(str, i + 1, *j - (i + 1));
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(new, tmp);
		free(tmp);
		if (!tmp2)
			return (NULL);
		return (tmp2);
	}
	return (NULL);
}

/* Need to strdup new, or it will do address = same address */
char	*join_no_quote(const char *str, char *new, int *j)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = NULL;
	i = *j;
	*j = i;
	if (str[*j])
		(*j)++;
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
	{
		tmp = ft_strdup(new);
		return (tmp);
	}
	tmp = ft_substr(str, i, *j - i);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(new, tmp);
	free(tmp);
	if (!tmp2)
		return (NULL);
	return (tmp2);
}

char	*inside_loop(const char *str, char *new, int *j)
{
	char	*tmp;

	tmp = NULL;
	while ((str[*j] == 34 && str[*j + 1] == 34)
		|| (str[*j] == 39 && str[*j + 1] == 39))
		*j = *j + 2;
	if ((str[*j] == 34 && str[*j + 1] != 34)
		|| (str[*j] == 39 && str[*j + 1] != 39))
	{
		tmp = loop_remove_quote(str, new, j);
		if (!tmp)
			return (NULL);
		if (str[*j])
			(*j)++;
	}
	else
	{
		tmp = join_no_quote(str, new, j);
		if (!tmp)
			return (NULL);
		if (*j > 0)
			if (str[*j - 1] == '<' || str[*j - 1] == '>')
				return (tmp);
	}
	return (tmp);
}
