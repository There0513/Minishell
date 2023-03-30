/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:27:14 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/17 14:14:42 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	double_check_env(char **envp, char **split, int i)
{
	if (!envp[i] || ft_strncmp(envp[i], "PATH", 4) != 0)
	{
		ft_putstr_fd(split[0], 2);
		ft_putstr_fd(": No such file or directory _double_check_env\n", 2);
		g_error = 127;
		return (-1);
	}
	return (1);
}

void	free_path(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}
