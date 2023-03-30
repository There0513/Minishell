/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:24:51 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/16 14:19:29 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 Deep copy swap
*/

void	ft_swap_a(t_list **a, char *tmp_key_b, char *tmp_value_b)
{
	t_envp	*envp;

	if (!a || !*a)
	{
		free(tmp_key_b);
		if (tmp_value_b)
			free(tmp_value_b);
	}
	envp = (*a)->content;
	free(envp->key);
	if (envp->value)
		free(envp->value);
	envp->key = tmp_key_b;
	envp->value = tmp_value_b;
}

void	ft_swap_b(t_list **b, char *tmp_key_a, char *tmp_value_a)
{
	t_envp	*envp;

	if (!b || !*b)
	{
		free(tmp_key_a);
		if (tmp_value_a)
			free(tmp_value_a);
	}
	envp = (*b)->content;
	free(envp->key);
	if (envp->value)
		free(envp->value);
	envp->key = tmp_key_a;
	envp->value = tmp_value_a;
}

int	ft_strdup_swap_a(t_list **a, char **tmp_key_a, char **tmp_value_a)
{
	t_envp	*envp;

	if (!a || !*a ||!tmp_key_a || !tmp_value_a)
		return (0);
	envp = (*a)->content;
	*tmp_key_a = ft_strdup(envp->key);
	if (!*tmp_key_a)
		return (0);
	if (envp->value)
		*tmp_value_a = ft_strdup(envp->value);
	else
		*tmp_value_a = NULL;
	return (1);
}

int	ft_strdup_swap_b(t_list **b, char **tmp_key_b, char **tmp_value_b)
{
	t_envp	*envp;

	if (!b || !*b ||!tmp_key_b || !tmp_value_b)
		return (0);
	envp = (*b)->content;
	*tmp_key_b = ft_strdup(envp->key);
	if (!*tmp_key_b)
		return (0);
	if (envp->value)
		*tmp_value_b = ft_strdup(envp->value);
	else
		*tmp_value_b = NULL;
	return (1);
}

void	ft_swap(t_list **a, t_list **b)
{
	char	*tmp_key_a;
	char	*tmp_value_a;
	char	*tmp_key_b;
	char	*tmp_value_b;

	tmp_key_a = NULL;
	tmp_key_b = NULL;
	tmp_value_a = NULL;
	tmp_value_b = NULL;
	if (!a || !b || !*a || !*b)
		return ;
	if (!ft_strdup_swap_a(a, &tmp_key_a, &tmp_value_a))
		return ;
	if (!ft_strdup_swap_b(b, &tmp_key_b, &tmp_value_b))
	{
		free(tmp_key_a);
		if (tmp_value_b)
			free(tmp_value_b);
		return ;
	}
	ft_swap_a(a, tmp_key_b, tmp_value_b);
	ft_swap_b(b, tmp_key_a, tmp_value_a);
}
