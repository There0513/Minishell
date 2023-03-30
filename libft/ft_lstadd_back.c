/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:52:39 by threiss           #+#    #+#             */
/*   Updated: 2021/12/27 15:32:49 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*begin;
	t_list	*lst;

	if (!new || !alst)
		return ;
	begin = *alst;
	if (*alst == 0)
		*alst = new;
	else
	{
		lst = ft_lstlast(*alst);
		while (begin->next)
			begin = begin->next;
		if (lst)
			new->head = lst;
		begin->next = new;
	}
}
