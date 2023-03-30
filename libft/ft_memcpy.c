/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:03:17 by threiss           #+#    #+#             */
/*   Updated: 2022/02/07 19:44:19 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst;
	const unsigned char	*sc;

	dst = (unsigned char *)dest;
	sc = (const unsigned char *)src;
	i = -1;
	if (n == 0 || dest == src)
		return (dest);
	while (++i < n)
		dst[i] = sc[i];
	return (dest);
}
