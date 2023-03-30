/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_to_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:43:12 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 11:45:24 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_redir	*put_redir_action_one(char *pipe, int *i,
	t_list **envp_lst, t_save_free **save_free)
{
	t_redir	*redir;

	redir = NULL;
	redir = check_add_redirections(pipe, i, envp_lst, save_free);
	(*save_free)->redir = redir;
	if (!redir)
		return (NULL);
	return (redir);
}

int	put_redir_action_two(t_action **action, t_redir **redir)
{
	t_list	*elem;

	elem = NULL;
	if ((*redir)->sign == -1)
	{
		if (*redir)
		{
			free((*redir)->here_doc_limiter);
			free(*redir);
		}
		if ((*action)->cmd)
			return (free_split_return((*action)->cmd, 0));
		else
			return (0);
	}
	add_redir_sign_to_action(redir);
	elem = ft_lstnew(*redir);
	if (elem)
		ft_lstadd_back(&(*action)->lst_redir, elem);
	return (1);
}

/*
 ** put in right structs ('actions') (redir, if (pipe at end) -> fds etc.)
 ** action will be added to t_list *action for execution
 */
int	put_cmds_in_t_action_lst(t_action **action,
	char *pipe, t_list **envp_lst, t_save_free **save_free)
{
	t_redir	*redir;
	int		i;
	int		ret;

	i = 0;
	while (pipe[i])
	{
		if (pipe[i] && pipe[i] != '<' && pipe[i] != '>')
		{
			i = put_in_lst_two(i, pipe, action);
			if (i == -1)
				return (-1);
		}
		if (pipe[i] && (pipe[i] == '<' || pipe[i] == '>'))
		{
			redir = put_redir_action_one(pipe, &i, envp_lst, save_free);
			if (redir)
				ret = put_redir_action_two(action, &redir);
			if (ret == -1 || ret == 0)
				return (ret);
		}
		if (pipe[i])
			i++;
	}
	return (1);
}

/*
 ** create t_action separeted by action
 ** (|, redir, cmd simple (annex cmd, args cmd, filename))
 */
int	check_get_action(t_list **actions, char *pipe,
	t_list **envp_lst, t_save_free **save_free)
{
	t_list		*elem;
	int			ret;

	if (!actions)
		return (-1);
	(*save_free)->action = malloc(sizeof(t_action));
	if (!(*save_free)->action)
		return (-1);
	init_action(&(*save_free)->action);
	ret = put_cmds_in_t_action_lst(&(*save_free)->action,
			pipe, envp_lst, save_free);
	if (ret != 1)
	{
		free((*save_free)->action);
		if (g_error == 0)
			ft_putstr_fd("Error\n", 2);
		return (ret);
	}
	if ((*save_free)->action)
	{
		elem = ft_lstnew((*save_free)->action);
		if (elem)
			ft_lstadd_back(actions, elem);
	}
	return (1);
}

/*
 ** get all pipes -> needed for execution, childs etc. 
 */
int	pipe_to_actions_t(char *str, t_list **envp_lst,
	t_list **action_t, t_save_free **save_free)
{
	int		i;
	int		ret;

	i = -1;
	if (str[0] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (-1);
	}
	(*save_free)->split = ft_split_parser(str, '|');
	while ((*save_free)->split[++i])
	{
		ret = check_get_action(action_t,
				(*save_free)->split[i], envp_lst, save_free);
		if (ret != 1)
			return (free_split_return((*save_free)->split, ret));
	}
	return (free_split_return((*save_free)->split, 1));
}
