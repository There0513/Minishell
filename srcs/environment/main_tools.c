/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:45:52 by gchopin           #+#    #+#             */
/*   Updated: 2022/01/26 17:21:26 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strlen_env(const char *s, int *i)
{
	if (!s)
		return ;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
	{
		(*i)++;
	}
}

char	*ft_strdup_get_env(const char *s)
{
	char	*ptr;
	int		i;

	i = -1;
	if (!s)
	{
		return (NULL);
	}
	ptr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (s[++i])
		ptr[i] = s[i];
	ptr[i] = '\0';
	return (ptr);
}

int	search_next_dollar(const char *env_str, int *i, int *end)
{
	if (env_str[*end] == '$')
	{
		*i = *end;
		return (search_dollar(env_str, i));
	}
	else
	{
		*i = *end;
		return (0);
	}
}
