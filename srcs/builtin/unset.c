/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:44:18 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/16 14:52:58 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_unset_str(const char *str)
{
	char	*tmp;
	int		i;
	int		start;

	start = loop_quotes(str);
	tmp = looping_way(str, &start);
	if (!tmp)
		return (NULL);
	i = 1;
	if (!ft_isalpha(tmp[0]) && tmp[0] != '_')
	{
		free(tmp);
		return (NULL);
	}
	while (str[i] && (ft_isalnum(tmp[i]) || tmp[i] == '_'))
		i++;
	if (tmp[i] && !ft_isalnum(tmp[i]) && tmp)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

char	*ft_unset_three(char *split, const char *str, int *ret,
	t_list **envp_lst)
{
	char	*tmp;

	tmp = NULL;
	if (split)
		tmp = check_unset_str(split);
	if (str && !tmp)
	{
		ft_putstr_fd("Identifiant not valid\n", 2);
		*ret = -1;
	}
	ft_unset_two(envp_lst, tmp);
	free(tmp);
	tmp = NULL;
	return (tmp);
}

int	ft_unset(t_list **envp_lst, const char *str)
{
	char	**split;
	char	*tmp;
	int		i;
	int		ret;

	if (!envp_lst || !*envp_lst)
		return (-1);
	if (!str)
		return (1);
	tmp = NULL;
	split = NULL;
	i = 0;
	ret = 1;
	split = ft_split_parser(str, ' ');
	if (!split)
		return (-1);
	while (split[i])
	{
		tmp = ft_unset_three(split[i], str, &ret, envp_lst);
		i++;
	}
	if (tmp)
		free(tmp);
	ft_free_split(split);
	return (ret);
}
