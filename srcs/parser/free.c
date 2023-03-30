/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:43:52 by threiss           #+#    #+#             */
/*   Updated: 2022/02/16 16:19:47 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_word_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_token	*token;

	token = NULL;
	(void)del;
	if (*lst != 0)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			token = (*lst)->content;
			free(token->str);
			free((*lst)->content);
			free(*lst);
			*lst = tmp;
		}
		*lst = 0;
	}
}

void	free_redir(t_list *lst_redir)
{
	t_redir	*redir;
	t_list	*tmp;

	if (lst_redir != 0)
	{
		while (lst_redir)
		{
			redir = lst_redir->content;
			if (redir->here_doc_limiter)
				free(redir->here_doc_limiter);
			if (redir->filename)
				free(redir->filename);
			if (redir->fd != -1)
				close(redir->fd);
			tmp = (lst_redir)->next;
			free((lst_redir)->content);
			free(lst_redir);
			lst_redir = tmp;
		}
		lst_redir = 0;
	}
	free(lst_redir);
}

void	free_action_elem(t_action *action)
{
	int	i;

	i = 0;
	free_redir(action->lst_redir);
	if (action->cmd)
	{
		while (action->cmd[i])
		{
			free(action->cmd[i]);
			i++;
		}
		free(action->cmd);
	}
	if (action->args_cmd)
		free(action->args_cmd);
}

void	ft_action_t_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	(void)del;
	tmp = NULL;
	if (*lst != 0)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			free_action_elem((*lst)->content);
			free((*lst)->content);
			free(*lst);
			*lst = tmp;
		}
		*lst = 0;
	}
}
