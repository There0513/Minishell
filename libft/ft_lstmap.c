/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:02:10 by threiss           #+#    #+#             */
/*   Updated: 2020/11/23 14:50:09 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*tmp;
	t_list	*next;

	begin = 0;
	if (lst != 0)
	{
		begin = ft_lstnew((*f)(lst->content));
		tmp = begin;
		while (lst->next)
		{
			next = ft_lstnew((*f)(lst->content));
			if (!next->content)
				(*del)(tmp->content);
			tmp->next = next;
			tmp = next;
			lst = lst->next;
		}
	}
	return (begin);
}
