/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:32:19 by threiss           #+#    #+#             */
/*   Updated: 2022/02/07 19:47:16 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(long nbr)
{
	int	size;

	if (nbr < 0)
	{
		size = 1;
		nbr *= -1;
	}
	else
		size = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		size++;
	}
	if (size == 0)
		return (1);
	return (size);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	long	nbr;

	nbr = n;
	size = get_size(nbr);
	ptr = malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (0);
	if (nbr < 0)
	{
		ptr[0] = '-';
		nbr *= -1;
	}
	ptr[size] = '\0';
	if (nbr == 0)
		ptr[0] = '0';
	while (nbr > 0)
	{
		ptr[--size] = nbr % 10 + 48;
		nbr /= 10;
	}
	return (ptr);
}
