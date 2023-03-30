/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:02:24 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/12 20:15:35 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/*
** create char **envp = create_envp(t_lst *envp_lst) for execution
*/

int	free_envp_cpy(char **envp_cpy)
{
	int	i;

	i = 0;
	if (envp_cpy)
	{
		free(envp_cpy[i]);
		i++;
	}
	free(envp_cpy);
	return (0);
}

int	create_envp_two(t_envp *envp, char **envp_cpy, int i)
{
	char	*tmp;

	if (!envp)
		return (0);
	envp_cpy[i] = ft_strjoin(envp->key, "=");
	if (!envp_cpy[i])
		return (free_envp_cpy(envp_cpy));
	tmp = ft_strjoin(envp_cpy[i], envp->value);
	free(envp_cpy[i]);
	if (!tmp)
		return (free_envp_cpy(envp_cpy));
	envp_cpy[i] = ft_strdup(tmp);
	free(tmp);
	if (!envp_cpy[i])
		return (free_envp_cpy(envp_cpy));
	return (1);
}

char	**create_envp(t_list *envp_lst)
{
	t_envp	*envp;
	char	**envp_cpy;
	int		len;
	int		i;

	len = ft_lstsize(envp_lst);
	i = 0;
	envp_cpy = malloc(sizeof(char *) * ++len);
	if (!envp_cpy)
		return (NULL);
	while (envp_lst)
	{
		envp = envp_lst->content;
		if (envp->value)
		{
			if (!create_envp_two(envp, envp_cpy, i))
				return (NULL);
			i++;
		}
		envp_lst = envp_lst->next;
	}
	envp_cpy[i] = NULL;
	return (envp_cpy);
}

int	ft_env(t_list *envp_lst)
{
	t_envp	*envp;

	if (!envp_lst)
		return (-1);
	while (envp_lst)
	{
		envp = envp_lst->content;
		if (envp->value)
			printf("%s=%s\n", envp->key, envp->value);
		envp_lst = envp_lst->next;
	}
	return (1);
}
