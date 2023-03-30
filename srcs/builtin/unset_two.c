/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:33:52 by threiss           #+#    #+#             */
/*   Updated: 2022/02/16 15:13:49 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   delete current pointer, at head
   give a way to ->next->head to go back in the list
 */

void	ft_unset_header(t_list **envp_lst)
{
	t_list	*tmp_next;
	t_envp	*envp;

	if (!envp_lst || !*envp_lst)
		return ;
	tmp_next = NULL;
	tmp_next = (*envp_lst)->next;
	envp = (*envp_lst)->content;
	free(envp->value);
	free(envp->key);
	free(envp);
	free(*envp_lst);
	*envp_lst = tmp_next;
	if (*envp_lst)
	{
		(*envp_lst)->head = NULL;
		if ((*envp_lst)->next)
			(*envp_lst)->next->head = *envp_lst;
	}
}

/*
   free content values, free current list
   give current pointer a head struct
   updating next, and ->next->head for proper navigating.
 */

void	ft_unset_middle(t_list **envp_lst)
{
	t_list	*tmp_head;
	t_list	*tmp_next;
	t_envp	*envp;

	if (!envp_lst || !*envp_lst)
		return ;
	tmp_head = NULL;
	tmp_next = NULL;
	tmp_head = (*envp_lst)->head;
	tmp_next = (*envp_lst)->next;
	envp = (*envp_lst)->content;
	free(envp->value);
	free(envp->key);
	free(envp);
	free(*envp_lst);
	*envp_lst = tmp_head;
	if (*envp_lst)
	{
		(*envp_lst)->next = tmp_next;
		if ((*envp_lst)->next)
			(*envp_lst)->next->head = *envp_lst;
	}
}

/*
   Choose removing content from head or anywhere
 */

void	ft_unset_lst(t_list **envp_lst)
{
	if (!envp_lst || !*envp_lst)
		return ;
	if ((*envp_lst)->head == NULL)
	{
		ft_unset_header(envp_lst);
	}
	else
	{
		ft_unset_middle(envp_lst);
	}
}

/*
   searching for value
   updating current list pointer (*envp_lst = (*envp_lst)->next;)
   saving first address to go back at the start of the list with lst_cpy
   in case no string has been found with ft_strcmp.
 */

void	ft_unset_two(t_list **envp_lst, const char *tmp)
{
	t_envp	*envp;

	envp = NULL;
	if (!envp_lst || !*envp_lst || !tmp)
		return ;
	while ((*envp_lst)->next)
	{
		envp = (*envp_lst)->content;
		if (envp && tmp && ft_strcmp(envp->key, tmp) == 0)
			ft_unset_lst(envp_lst);
		*envp_lst = (*envp_lst)->next;
	}
	if (*envp_lst)
	{
		envp = (*envp_lst)->content;
		if (envp && tmp && ft_strcmp(envp->key, tmp) == 0)
			ft_unset_lst(envp_lst);
		while ((*envp_lst)->head)
			*envp_lst = (*envp_lst)->head;
	}
}
