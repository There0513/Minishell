/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:58:00 by threiss           #+#    #+#             */
/*   Updated: 2022/02/16 16:23:55 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	simple_parse_cmd(t_action **action)
{
	char	*str;
	int		i;
	int		start;

	str = NULL;
	i = 0;
	if (!action || !action)
		return ;
	while ((*action)->cmd[i])
	{
		start = 0;
		str = looping_way((*action)->cmd[i], &start);
		free((*action)->cmd[i]);
		(*action)->cmd[i] = str;
		i++;
	}
}

int	get_args_two(t_action **action, char **split, char **tmp_cmd, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (!action || !tmp_cmd || !split)
		return (0);
	tmp = ft_strjoin(*tmp_cmd, " ");
	free(*tmp_cmd);
	if (!tmp)
		return (0);
	*tmp_cmd = ft_strjoin(tmp, split[*i]);
	free(tmp);
	if (!*tmp_cmd)
		return (0);
	tmp = ft_strjoin((*action)->args_cmd, " ");
	free((*action)->args_cmd);
	if (!tmp)
		return (0);
	(*action)->args_cmd = ft_strjoin(tmp, split[*i]);
	free(tmp);
	if (!(*action)->args_cmd)
		return (0);
	return (1);
}

int	get_args_one(t_action **action, char **split, char **tmp_cmd, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (!action || !tmp_cmd || !split)
		return (0);
	if (!(*action)->args_cmd)
	{
		(*action)->args_cmd = ft_strdup(split[*i]);
		if (!(*action)->args_cmd)
			return (0);
		tmp = ft_strjoin(*tmp_cmd, " ");
		free(*tmp_cmd);
		if (!tmp)
			return (0);
		*tmp_cmd = ft_strjoin(tmp, split[*i]);
		free(tmp);
		if (!*tmp_cmd)
			return (0);
	}
	else
	{
		if (!get_args_two(action, split, tmp_cmd, i))
			return (0);
	}
	return (1);
}

int	loop_tmp_cmd(t_action **action, char **split, char **tmp_cmd, int *i)
{
	if (!action || !split || !tmp_cmd)
		return (-1);
	while (split[*i])
	{
		if (!get_args_one(action, split, tmp_cmd, i))
			return (0);
		(*i)++;
	}
	return (1);
}

int	check_echo_option(char *str, char **tmp_cmd)
{
	char	*tmp;
	size_t	i;

	tmp = NULL;
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (i != ft_strlen(str))
		return (0);
	tmp = ft_strjoin(*tmp_cmd, " ");
	free(*tmp_cmd);
	*tmp_cmd = ft_strjoin(tmp, "-n");
	free(tmp);
	return (1);
}
