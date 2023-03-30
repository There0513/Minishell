/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:37:49 by threiss           #+#    #+#             */
/*   Updated: 2022/02/07 19:52:24 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	join_two(int *l_s1, int *l_s2, char const *s1, char const *s2)
{
	if (s1)
		*l_s1 = ft_strlen(s1);
	if (s2)
		*l_s2 = ft_strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;
	int		l_s1;
	int		l_s2;

	i = -1;
	j = -1;
	l_s1 = 0;
	l_s2 = 0;
	if (!s1)
		return (0);
	join_two(&l_s1, &l_s2, s1, s2);
	ptr = malloc((l_s1 + l_s2 + 1) * sizeof(char));
	if (!ptr)
		return (0);
	if (s1)
		while (s1[++i])
			ptr[i] = s1[i];
	if (s2)
		while (s2[++j])
			ptr[i++] = s2[j];
	ptr[i] = '\0';
	return (ptr);
}
