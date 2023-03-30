/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:03:50 by threiss           #+#    #+#             */
/*   Updated: 2022/02/07 19:36:01 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		if (((unsigned char *)src)[i] == (unsigned char)c && i < ft_strlen(src))
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			return ((unsigned char *)dest + i + 1);
		}
		if (!(((unsigned char *)src)[i] == (unsigned char)c))
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	}
	return (0);
}
