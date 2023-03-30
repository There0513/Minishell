/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:55:35 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 13:53:15 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp_elem(t_envp *envp_lst)
{
	if (envp_lst->key)
		free(envp_lst->key);
	if (envp_lst->value)
		free(envp_lst->value);
}

void	ft_envp_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	(void)del;
	if (*lst != 0)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free_envp_elem((*lst)->content);
			free((*lst)->content);
			free(*lst);
			*lst = tmp;
		}
		*lst = 0;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
		free(split);
		split = NULL;
	}
}
