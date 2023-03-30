/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:18:24 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/08 19:49:31 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	loop_values(char const *s, char c, size_t *i)
{
	size_t	save_quote;

	save_quote = 0;
	while (s[*i] != '\0' && s[*i] != c)
	{
		if (s[*i] == 34 || s[*i] == 39)
		{
			save_quote = *i;
			(*i)++;
			while (s[*i] && s[*i] != s[save_quote])
				(*i)++;
		}
		if (s[*i])
			(*i)++;
	}
}

static size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	nb_word;

	i = 0;
	nb_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			nb_word++;
			loop_values(s, c, &i);
		}
		else
			i++;
	}
	return (nb_word);
}

static void	*ft_free(char **ptr, size_t size)
{
	size++;
	if (ptr)
	{
		while (size != 0)
		{
			size--;
			free(ptr[size]);
		}
		free(ptr);
	}
	return (NULL);
}

static	char	*crea_arr(char const *s, char c, char *ptr, size_t *i)
{
	unsigned int	start;
	size_t			end;

	start = 0;
	end = 0;
	while (s[*i] == c && s[*i] != '\0')
		*i = *i + 1;
	if (s[*i] != c && s[*i] != '\0')
		start = *i;
	loop_values(s, c, i);
	if (s[*i] == c || s[*i] == '\0')
	{
		end = *i;
		*i = *i + 1;
	}
	return (ptr = ft_substr(s, start, (end - start)));
}

char	**ft_split_parser(char const *s, char c)
{
	char			**ptr;
	size_t			nb_word;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	nb_word = count_word(s, c);
	ptr = malloc(sizeof(char const *) * (nb_word + 1));
	if (ptr == NULL)
		return (NULL);
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (nb_word > j)
	{
		ptr[j] = crea_arr(s, c, ptr[j], &i);
		if (ptr[j] == NULL)
			return (ft_free(ptr, j));
		j++;
	}
	ptr[j] = 0;
	return (ptr);
}
