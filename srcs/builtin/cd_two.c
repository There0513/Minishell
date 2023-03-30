/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_two.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:00:37 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/09 16:30:40 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_home(t_list **envp_lst)
{
	t_envp	*envp;
	char	*path;

	if (!envp_lst || !*envp_lst)
		return (NULL);
	while (*envp_lst)
	{
		envp = (*envp_lst)->content;
		if (envp && ft_strcmp(envp->key, "HOME") == 0)
		{
			path = envp->value;
			return (ft_strdup(path));
		}
		envp_lst = &(*envp_lst)->next;
	}
	return (NULL);
}

char	envp_exist(t_list **envp_lst, char *str)
{
	t_envp	*envp;

	envp = NULL;
	while (*envp_lst)
	{
		envp = (*envp_lst)->content;
		if (!ft_strcmp(envp->key, str))
			return (1);
		envp_lst = &(*envp_lst)->next;
	}
	return (0);
}

char	*update_old_pwd_two(t_list **envp_lst)
{
	t_envp	*envp;

	envp = NULL;
	if (!envp_lst || !*envp_lst)
		return (NULL);
	while (*envp_lst)
	{
		envp = (*envp_lst)->content;
		if (envp && !ft_strcmp(envp->key, "PWD"))
			return (envp->value);
		envp_lst = &(*envp_lst)->next;
	}
	return (NULL);
}

void	update_old_pwd_one(t_list **envp_lst)
{
	t_envp	*envp;
	char	*save;

	envp = NULL;
	save = NULL;
	if (!envp_lst || !*envp_lst)
		return ;
	save = update_old_pwd_two(envp_lst);
	if (!save)
		return ;
	while (*envp_lst)
	{
		envp = (*envp_lst)->content;
		if (envp && !ft_strcmp(envp->key, "OLDPWD"))
		{
			free(envp->value);
			envp->value = ft_strdup(save);
			return ;
		}
		envp_lst = &(*envp_lst)->next;
	}
}

int	cd_error_check(t_action *action)
{
	if (action->args_cmd && ft_strchr(action->args_cmd, ' ') != NULL)
	{
		printf("cd: too many arguments\n");
		return (-1);
	}
	return (0);
}
