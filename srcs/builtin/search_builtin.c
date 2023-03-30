/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:46:21 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/16 15:40:38 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	search_builtin_four(const char *str, t_action *action, t_list **envp_lst)
{
	int	res;

	if (!action || !envp_lst || !*envp_lst)
		return (-1);
	if (!ft_strcmp(str, "unset"))
	{
		res = ft_unset(envp_lst, action->args_cmd);
		if (res == -1)
			g_error = 1;
		return (res);
	}
	return (0);
}

int	search_builtin_three(const char *str, t_action *action, t_list **envp_lst)
{
	int	res;

	if (!action || !envp_lst || !*envp_lst)
		return (-1);
	if (!ft_strcmp(str, "pwd"))
	{
		res = ft_pwd(*envp_lst);
		if (res == -1)
			g_error = 1;
		return (res);
	}
	if (!ft_strcmp(str, "env"))
	{
		res = ft_env(*envp_lst);
		if (res == -1)
			g_error = 1;
		return (res);
	}
	if (!ft_strcmp(str, "exit"))
		ft_exit(&action);
	return (search_builtin_four(str, action, envp_lst));
}

int	search_builtin_two(const char *str, t_action *action, t_list **envp_lst)
{
	int	res;

	if (!action || !envp_lst || !*envp_lst)
		return (-1);
	if (!ft_strcmp(str, "cd"))
	{
		res = ft_cd(&action, envp_lst);
		if (res == -1)
			g_error = 1;
		return (res);
	}
	if (!ft_strcmp(str, "export"))
	{
		res = ft_export(envp_lst, action->args_cmd, action->cmd[1]);
		if (res == -1)
			g_error = 1;
		return (res);
	}
	return (search_builtin_three(str, action, envp_lst));
}

int	search_builtin(const char *str, t_action *action, t_list **envp_lst)
{
	int	res;

	if (!action || !envp_lst || !*envp_lst)
		return (-1);
	if (action && !ft_strcmp(str, "echo"))
	{
		if (!action->args_cmd)
		{
			res = ft_echo(action->args_cmd, action->cmd[1]);
			return (res);
		}
		res = ft_echo(action->args_cmd, action->cmd[1]);
		return (res);
	}
	res = search_builtin_two(str, action, envp_lst);
	return (res);
}
