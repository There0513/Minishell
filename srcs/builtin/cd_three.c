/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_three.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:58:27 by threiss           #+#    #+#             */
/*   Updated: 2022/02/16 15:37:47 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_old(t_list **envp_lst)
{
	t_envp	*envp;
	char	*path;

	if (!envp_lst || !*envp_lst)
		return (NULL);
	while (*envp_lst)
	{
		envp = (*envp_lst)->content;
		if (envp && ft_strcmp(envp->key, "OLDPWD") == 0)
		{
			path = envp->value;
			return (ft_strdup(path));
		}
		envp_lst = &(*envp_lst)->next;
	}
	return (NULL);
}

/* added + ft_strlen(*current_path) to get new path for PWD */
char	*update_pwd_main(t_list **envp_lst, char **current_path)
{
	char	*tmp;

	if (!current_path)
		return (NULL);
	tmp = NULL;
	if (*current_path && chdir(*current_path) == -1)
	{
		free(*current_path);
		*current_path = NULL;
		perror("Error ");
		return (NULL);
	}
	tmp = NULL;
	tmp = getcwd(tmp, get_path_size(envp_lst) + ft_strlen(*current_path) + 1);
	if (!envp_exist(envp_lst, "PWD"))
		ft_export(envp_lst, "PWD=", NULL);
	update_pwd(envp_lst, tmp);
	free(tmp);
	return (tmp);
}

void	ft_cd_three(t_list **envp_lst, char **current_path)
{
	char	*tmp_cwd;
	char	*tmp;

	tmp = NULL;
	if (!envp_lst || !current_path)
		return ;
	if (!envp_exist(envp_lst, "OLDPWD"))
	{
		tmp_cwd = getcwd(tmp, get_path_size(envp_lst) + 1);
		if (!tmp_cwd)
		{
			free(*current_path);
			return ;
		}
		tmp = ft_strjoin("OLDPWD=", tmp_cwd);
		free(tmp_cwd);
		if (!tmp)
		{
			free(*current_path);
			return ;
		}
		ft_export(envp_lst, tmp, NULL);
		free(tmp);
	}
}

int	get_current_path(t_action **action, char **current_path, t_list **envp_lst)
{
	if (ft_strcmp((*action)->cmd[1], "-") == 0)
		*current_path = search_old(envp_lst);
	else
		*current_path = ft_cd_start(envp_lst, (*action)->args_cmd);
	if (!*current_path)
		return (-1);
	if (ft_strcmp((*action)->cmd[1], "-") == 0)
		printf("%s\n", *current_path);
	return (1);
}
