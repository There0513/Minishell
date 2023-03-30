/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:55:52 by threiss           #+#    #+#             */
/*   Updated: 2022/02/16 15:31:42 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_checker(const char *val)
{
	if (val && ft_strcmp(val, "-") == 0)
	{
		write(2, "export bad variable name\n", 25);
		return (-1);
	}
	return (1);
}

int	export_checker_two(char **split, int i, t_list **envp_lst, int *ret)
{
	t_envp	*elem;

	elem = malloc(sizeof(t_envp));
	if (!elem)
	{
		ft_free_split(split);
		return (-1);
	}
	if (ft_export_two(&elem, split[i], ret))
	{
		ft_free_split(split);
		return (-1);
	}
	if (elem && search_elem_into_envp(envp_lst, elem))
	{
		free(elem->key);
		free(elem);
	}
	return (0);
}

int	search_envp_two(t_envp *envp, t_envp *elem)
{
	if (!ft_strcmp(envp->key, elem->key))
	{
		free(envp->value);
		envp->value = elem->value;
		return (1);
	}
	return (0);
}

void	parse_export_val_two(int *cpy_i, char **value, int equal_ok)
{
	char	*tmp;

	*cpy_i = loop_quotes(*value);
	tmp = looping_way(*value, cpy_i);
	free(*value);
	*value = tmp;
	if (equal_ok == 0)
	{
		free(*value);
		*value = NULL;
	}
}

int	parse_export_key_two(char **key, const char *str, int *i, char **tmp)
{
	*key = ft_substr(str, 0, *i);
	if (!*key)
		return (0);
	*i = loop_quotes(*key);
	*tmp = looping_way(*key, i);
	free(*key);
	*key = *tmp;
	return (1);
}
