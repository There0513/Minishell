/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 00:53:47 by threiss           #+#    #+#             */
/*   Updated: 2022/01/20 14:45:38 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	ptr = malloc((sizeof(char) * len) + 1);
	if (ptr == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		ptr[i] = '\0';
		return (ptr);
	}
	while (len > i && s[start] != '\0')
	{
		ptr[i] = (char)s[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
