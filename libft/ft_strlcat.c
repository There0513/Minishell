/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:11:53 by threiss           #+#    #+#             */
/*   Updated: 2020/11/24 15:58:46 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	i_src;

	len_dst = ft_strlen(dst);
	i_src = 0;
	if (len_dst > size)
		return (size + ft_strlen(src));
	if (size < len_dst + 1)
		return (len_dst + ft_strlen(src));
	while (src[i_src] && i_src < (size - len_dst - 1))
	{
		dst[len_dst + i_src] = src[i_src];
		i_src++;
	}
	dst[len_dst + i_src] = '\0';
	if (len_dst <= size)
		return (ft_strlen(src) + len_dst);
	return (len_dst + i_src);
}
