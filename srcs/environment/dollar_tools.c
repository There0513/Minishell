/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:57:05 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/08 11:36:04 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Need to strjoin start of current string with old string
 */

static char	*fuse_start_dollar(char *tmp, char *end, char *value)
{
	if (!tmp)
	{
		free(end);
		return (NULL);
	}
	value = ft_strjoin(end, tmp);
	free(tmp);
	free(end);
	tmp = NULL;
	end = NULL;
	if (!value)
		return (NULL);
	return (value);
}

/* Need to join start of string until first $
   get env value
   move until end of alphabet
   Need to move current *i until we meet normal $env
 */
char	*find_dollar_three(t_list **envp_lst, char *str, char *end, int *i)
{
	char	*tmp;
	char	*value;

	value = NULL;
	tmp = ft_substr(str, 0, *i);
	if (!tmp)
	{
		free(end);
		return (NULL);
	}
	value = fuse_start_dollar(tmp, end, value);
	if (!value)
		return (NULL);
	tmp = find_dollar_four(envp_lst, str, value, i);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	end = fuse_end_dollar(end, value, tmp);
	if (!end)
		return (NULL);
	while (*i > 0 && str[*i] && str[*i] == '$' && str[*i - 1] == '$')
		(*i)--;
	return (end);
}

/*
 ** loop until $
 ** handling end of string ex $USER$ otherwise it will ignore last $
 ** function in dollar_tools_three.c
 */

void	find_dollar_two(t_list **envp_lst, char **str, char **end, int len_str)
{
	int	i;
	int	j;
	int	addition_quote;

	i = 0;
	j = 0;
	if (!envp_lst || !*envp_lst || !str || !str[0])
		return ;
	while (len_str > i && str[0][j++] && *str)
	{
		addition_quote = go_to_dollar(str, end, &len_str, &i);
		if (len_str > i && *str && str[0][i] == '$' && i >= 0)
		{
			*end = find_dollar_three(envp_lst, str[0], *end, &i);
			if (!*end)
				return ;
			*str += i;
			j = 0;
			i = add_quotes_in_end(str, end, 0, addition_quote);
		}
		if (*str)
			len_str = ft_strlen(*str);
	}
}

char	*find_dollar(char *str, t_list **envp_lst)
{
	char	*tmp;
	char	*end;

	if (!envp_lst)
		return (NULL);
	end = ft_strdup("");
	if (!end)
		return (NULL);
	if (str)
	{
		find_dollar_two(envp_lst, &str, &end, ft_strlen(str));
	}
	tmp = ft_strjoin(end, str);
	free(end);
	return (tmp);
}
