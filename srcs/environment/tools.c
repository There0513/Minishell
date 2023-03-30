/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:32:16 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/12 20:17:59 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_shlvl(t_list **envp_lst)
{
	t_envp	*envp;
	int		tmp;

	envp = NULL;
	tmp = 0;
	if (!envp_lst || !*envp_lst)
		return ;
	while (*envp_lst)
	{
		envp = (*envp_lst)->content;
		if (envp && ft_strcmp(envp->key, "SHLVL") == 0)
		{
			tmp = ft_atoi(envp->value);
			tmp++;
			if (envp->value)
				free(envp->value);
			envp->value = ft_itoa(tmp);
		}
		envp_lst = &(*envp_lst)->next;
	}
}

/* FIND PWD PATH SIZE */

size_t	get_path_size(t_list **envp_lst)
{
	t_envp	*envp;
	int		len;

	envp = NULL;
	len = 0;
	if (!envp_lst || !*envp_lst)
		return (0);
	while (*envp_lst)
	{
		envp = (*envp_lst)->content;
		if (envp && ft_strcmp(envp->key, "PWD") == 0)
		{
			len = ft_strlen(envp->value);
		}
		envp_lst = &(*envp_lst)->next;
	}
	if (len == 0)
		len = UCHAR_MAX;
	return (len);
}

/*
**	envp_var = key + value
*/

int	create_envp_var(char *str, t_envp **envp_var)
{
	int	i;

	i = 0;
	if (!envp_var || !str)
		return (1);
	*envp_var = malloc(sizeof(t_envp));
	if (!*envp_var)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	(*envp_var)->key = ft_substr(str, 0, i);
	if (!(*envp_var)->key)
	{
		free(*envp_var);
		return (0);
	}
	(*envp_var)->value = ft_strdup(&str[i + 1]);
	if (!(*envp_var)->value)
	{
		free((*envp_var)->key);
		free(*envp_var);
		return (0);
	}
	return (1);
}

int	create_envp_lst(char **envp, t_list **envp_lst)
{
	t_envp	*envp_var;
	t_list	*lst_elem;

	envp_var = NULL;
	lst_elem = NULL;
	if (!envp)
		return (0);
	while (*envp)
	{
		if (!create_envp_var(*envp, &envp_var))
			return (0);
		lst_elem = ft_lstnew(envp_var);
		if (!lst_elem)
		{
			free(envp_var->key);
			free(envp_var->value);
			free(envp_var);
			return (0);
		}
		ft_lstadd_back(envp_lst, lst_elem);
		envp++;
	}
	return (1);
}

int	initialize_env(char **envp, t_list **envp_lst, char *cwd)
{
	if (!envp_lst || !envp)
		return (1);
	if (!*envp)
	{
		ft_putstr_fd("No env variable set.\n", 2);
		return (2);
	}
	if (!create_envp_lst(envp, envp_lst))
	{
		if (cwd)
			free(cwd);
		perror("Error create_envp_lst");
		return (1);
	}
	find_shlvl(envp_lst);
	return (0);
}
