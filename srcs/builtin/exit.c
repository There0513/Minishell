/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 10:55:22 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 11:56:29 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	free_nd_exit(t_action **action, int exit_status)
{
	int	i;

	i = -1;
	if (!action || !*action)
		return (0);
	while ((*action)->cmd[++i])
		free((*action)->cmd[i]);
	free((*action)->cmd);
	free((*action)->args_cmd);
	free(*action);
	exit(exit_status);
	return (1);
}

char	*get_first_arg(char *str)
{
	char	*arg;
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			break ;
	arg = ft_substr(str, 0, i);
	return (arg);
}

int	seek_args(t_action **action, int *ac, int *i)
{
	if (!action || !*action)
		return (0);
	if ((*action)->args_cmd)
	{
		*ac = 1;
		while ((*action)->args_cmd[++(*i)])
			if ((*action)->args_cmd[*i] == ' ')
				(*ac)++;
	}
	else
	{
		if (!free_nd_exit(action, 0))
			return (0);
	}
	*i = -1;
	return (1);
}

int	execute_exit_args(t_action **action, int ac)
{
	char	*str;
	int		status;

	if (ac > 1)
	{
		printf("exit\nexit: too many arguments\n");
		g_error = 1;
		return (1);
	}
	else
	{
		str = get_first_arg((*action)->args_cmd);
		if (str && ft_strlen(str) > 10)
		{
			printf("exit\nexit: %s: numeric argument required\n", str);
			free_nd_exit(action, 2);
		}
		status = ft_atoi(str);
		free(str);
		free_nd_exit(action, status);
	}
	return (0);
}

int	ft_exit(t_action **action)
{
	char	*str;
	int		i;
	int		ac;

	ac = 0;
	i = -1;
	if (!action || !*action || !seek_args(action, &ac, &i))
		return (0);
	while ((*action)->args_cmd[++i] && (*action)->args_cmd[i] != ' ')
	{
		if (!ft_isdigit((*action)->args_cmd[i]))
		{
			str = get_first_arg((*action)->args_cmd);
			ft_putstr_fd("exit\nexit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			free(str);
			if (!free_nd_exit(action, 2))
				return (0);
		}
	}
	if (execute_exit_args(action, ac) == 1)
		return (1);
	free_nd_exit(action, 1);
	return (0);
}
