/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:05:21 by threiss           #+#    #+#             */
/*   Updated: 2022/02/07 19:42:56 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_words(char const *s, char c)
{
	int		i;
	int		words;

	i = 1;
	if (s[0] != c)
		words = 1;
	else
		words = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i - 1] == c && s[i])
		{
			words++;
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i_res;
	int		i;
	int		len;

	i_res = -1;
	i = 0;
	res = malloc((ft_get_words(s, c) + 1) * sizeof(char *));
	if (!s || !res)
		return (0);
	while (s[i] && ft_get_words(s, c) > 0)
	{
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			len++;
			i++;
		}
		if (len > 0)
			res[++i_res] = ft_substr(s, i - len, len);
	}
	res[++i_res] = 0;
	return (res);
}
