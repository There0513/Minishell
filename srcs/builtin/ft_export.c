/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 09:36:16 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/16 15:32:23 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_export_value(const char *str)
{
	char	*value;
	int		i;
	int		cpy_i;
	int		equal_ok;

	equal_ok = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		equal_ok = 1;
	cpy_i = i;
	if (str[cpy_i])
		cpy_i++;
	i = ft_read_path(str, cpy_i);
	value = ft_substr(str, cpy_i, i - cpy_i);
	if (!value)
		return (NULL);
	parse_export_val_two(&cpy_i, &value, equal_ok);
	return (value);
}

char	*parse_export_key(const char *str)
{
	char	*key;
	char	*tmp;
	int		i;

	key = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (parse_export_key_two(&key, str, &i, &tmp) == 0)
				return (NULL);
			break ;
		}
		i++;
	}
	if (!str[i])
		if (parse_export_key_two(&key, str, &i, &tmp) == 0)
			return (NULL);
	return (key);
}

char	search_elem_into_envp(t_list **envp_lst, t_envp *elem)
{
	t_list	*lst;
	t_envp	*envp;

	envp = NULL;
	if (!elem)
		return (0);
	while ((*envp_lst)->next)
	{
		envp = (*envp_lst)->content;
		if (!ft_strcmp(envp->key, elem->key))
		{
			free(envp->value);
			envp->value = elem->value;
			return (1);
		}
		envp_lst = &(*envp_lst)->next;
	}
	envp = (*envp_lst)->content;
	if (search_envp_two(envp, elem) == 1)
		return (1);
	lst = ft_lstnew(elem);
	ft_lstadd_back(envp_lst, lst);
	return (0);
}

int	ft_export_two(t_envp **elem, const char *str, int *ret)
{
	if (!*elem || !str)
		return (1);
	(*elem)->key = parse_export_key(str);
	if (!(*elem)->key || ((*elem)->key && !check_key_value((*elem)->key)))
	{
		write(2, "export bad variable name\n", 25);
		if ((*elem)->key)
			free((*elem)->key);
		free(*elem);
		*elem = NULL;
		*ret = -1;
		return (0);
	}
	(*elem)->value = parse_export_value(str);
	return (0);
}

int	ft_export(t_list **envp_lst, const char *str, const char *val)
{
	char	**split;
	int		i;
	int		ret;

	split = NULL;
	i = 0;
	ret = export_checker(val);
	if (!envp_lst || !*envp_lst)
		return (-1);
	if (!str)
	{
		ft_export_display(envp_lst);
		return (1);
	}
	split = ft_split_parser(str, ' ');
	if (!split)
		return (-1);
	while (split[i])
	{
		if (export_checker_two(split, i, envp_lst, &ret) == -1)
			return (-1);
		i++;
	}
	ft_free_split(split);
	return (ret);
}
