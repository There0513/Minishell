/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:24:32 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/17 14:52:05 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_dollar(const char *env_str, int *i)
{
	if (!env_str)
		return (-1);
	while (env_str[*i] && env_str[*i] != '$')
	{
		if (env_str[*i] == '$')
			return (1);
		(*i)++;
	}
	if (env_str[*i] == '$')
		return (1);
	return (0);
}

/*
 ** Moving next cpy lst, not original lst
 */

static char	*loop_env(t_list **lst, const char *str)
{
	t_envp	*envp;

	if (!lst || !*lst)
		return (NULL);
	while ((*lst)->next)
	{
		envp = (*lst)->content;
		if (!ft_strcmp(envp->key, str))
		{
			return (envp->value);
		}
		lst = &(*lst)->next;
	}
	if (*lst)
	{
		envp = (*lst)->content;
		if (!ft_strcmp(envp->key, str))
		{
			return (envp->value);
		}
	}
	return (NULL);
}

/*
 ** strdup segfault if loop_env return NULL
 **so just make "new" strdup return NULL if !s
 */
static char	*fill_value(t_list **lst, char **value, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (lst && *lst && value && str && *str)
	{
		tmp = ft_strdup_get_env(loop_env(lst, *str));
		if (!tmp)
			return (NULL);
		free(*str);
		if (!*value)
			*value = tmp;
		else
		{
			free(tmp2);
			tmp2 = ft_strjoin(*value, tmp);
			free(tmp);
			if (!tmp2)
				return (NULL);
			free(*value);
			*value = tmp2;
		}
	}
	return (*value);
}

static int	loop_environment(t_list **lst, int *i,
		const char *env_str, char **value)
{
	char	*str;
	int		end;

	end = *i + 1;
	ft_strlen_env(env_str, &end);
	str = ft_substr(env_str, *i + 1, end - (*i + 1));
	*i = end;
	if (!str)
	{
		return (-1);
	}
	if (fill_value(lst, value, &str) == NULL)
	{
		free(str);
		return (-1);
	}
	return (search_next_dollar(env_str, i, &end));
}

int	expand_environment(t_list **lst, const char *env_str, char **value)
{
	int		i;
	char	dollar;

	i = 0;
	dollar = 0;
	if (!env_str || !lst || !*lst)
		return (0);
	dollar = search_dollar(env_str, &i);
	if (dollar == -1)
		return (0);
	while (dollar == 1)
	{
		dollar = loop_environment(lst, &i, env_str, value);
		if (dollar == -1)
		{
			return (i);
		}
	}
	return (i);
}
