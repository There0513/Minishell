/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:16:10 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/16 15:40:06 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_list **envp_lst, char *current_path)
{
	t_envp	*envp;

	envp = NULL;
	if (!envp_lst || !*envp_lst || !current_path)
		return ;
	while (*envp_lst)
	{
		envp = (*envp_lst)->content;
		if (envp && !ft_strcmp(envp->key, "PWD"))
		{
			free(envp->value);
			envp->value = ft_strdup(current_path);
			return ;
		}
		envp_lst = &(*envp_lst)->next;
	}
}

/*
 cd alone use $HOME set current_path
 if start with / current_path = path
 if path is . or ..
 if .. or .. : chdir do the work itself set current_path
 if (!current_path) : tmp = getcwd + / + current_path ; free(current_folder);
 current_foler = tmp;
 update OLDPWD
 chdir
 update PWD
*/

char	*ft_cd_start(t_list **envp_lst, const char *path)
{
	char	*current_path;
	int		start_quote;
	int		end_quote;

	current_path = NULL;
	if (!path || (path && path[0] == '\0'))
	{
		current_path = search_home(envp_lst);
		if (!current_path)
			return (NULL);
	}
	else
	{
		start_quote = loop_quotes(path);
		end_quote = start_quote;
		current_path = looping_way(path, &end_quote);
		if (!current_path)
			return (NULL);
	}
	return (current_path);
}

char	*ft_cd_absolute(t_list **envp_lst, char *current_path)
{
	char	*save;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	save = current_path;
	if (current_path && current_path[0] != '/')
	{
		tmp = getcwd(tmp, get_path_size(envp_lst) + 1);
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(tmp, "/");
		free(tmp);
		if (!tmp2)
			return (NULL);
		tmp = ft_strjoin(tmp2, current_path);
		free(current_path);
		free(tmp2);
		return (tmp);
	}
	return (save);
}

int	ft_cd_two(t_list **envp_lst, char **current_path)
{
	if (!envp_lst || !current_path || !*current_path)
		return (0);
	ft_cd_three(envp_lst, current_path);
	update_old_pwd_one(envp_lst);
	if (!update_pwd_main(envp_lst, current_path))
	{
		free(*current_path);
		return (0);
	}
	free(*current_path);
	return (1);
}

int	ft_cd(t_action **action, t_list **envp_lst)
{
	char	*current_path;
	char	*tmp;

	if (!action || !envp_lst)
		return (-1);
	if (cd_error_check(*action) == -1)
		return (-1);
	if (get_current_path(action, &current_path, envp_lst) == -1)
		return (-1);
	tmp = ft_cd_absolute(envp_lst, current_path);
	if (!tmp)
	{
		if (current_path)
			free(current_path);
		return (-1);
	}
	current_path = ft_strdup(tmp);
	free(tmp);
	if (!ft_cd_two(envp_lst, &current_path))
	{
		if (current_path)
			free(current_path);
		return (-1);
	}
	return (1);
}
