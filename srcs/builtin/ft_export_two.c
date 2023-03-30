/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:15:16 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/16 14:18:57 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key_value(const char *str)
{
	int	i;

	i = 1;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] && !ft_isalnum(str[i]) && str[i] != '_')
		return (0);
	return (1);
}

int	ft_sort_two(t_list **envp_lst, t_envp *envp_current, t_list *first)
{
	t_list	**next;
	t_envp	*envp_next;

	envp_next = NULL;
	if (envp_lst && envp_current
		&& first && *envp_lst && (*envp_lst)->next)
	{
		envp_next = (*envp_lst)->next->content;
		if (envp_next && ft_strcmp(envp_current->key, envp_next->key) > 0)
		{
			next = NULL;
			next = envp_lst;
			if (next)
			{
				next = &(*next)->next;
				ft_swap(envp_lst, next);
			}
			*envp_lst = first;
			return (1);
		}
	}
	return (0);
}

void	ft_sort_one(t_list **envp_lst)
{
	t_list	*first;
	t_envp	*envp_current;
	int		boolean_loop;

	boolean_loop = 0;
	if (!envp_lst)
		return ;
	first = *envp_lst;
	while (*envp_lst)
	{
		envp_current = (*envp_lst)->content;
		if ((*envp_lst)->next)
		{
			boolean_loop = ft_sort_two(envp_lst, envp_current, first);
		}
		if (boolean_loop == 0)
			*envp_lst = (*envp_lst)->next;
		boolean_loop = 0;
	}
	*envp_lst = first;
}

void	ft_export_display(t_list **envp_lst)
{
	t_envp	*envp;

	if (!envp_lst)
		return ;
	ft_sort_one(envp_lst);
	while (*envp_lst)
	{
		envp = (*envp_lst)->content;
		printf("declare -x %s", envp->key);
		if (envp->value)
			printf("=\"%s\"\n", envp->value);
		else
			printf("\n");
		envp_lst = &(*envp_lst)->next;
	}
}
