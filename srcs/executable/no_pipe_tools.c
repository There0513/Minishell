/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:08:41 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/17 12:13:01 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_pipe_child_proc(char **split, char **envp, char **paths,
	t_save_free **save_free)
{
	struct stat	sb;

	if (!split || !envp || !paths)
		return (-1);
	if (split[0][0] == '/' || (split[0][0] == '.' && split[0][1] == '/')
		|| stat(split[0], &sb) == 0)
	{
		if (access(split[0], F_OK) == 0)
			execve(split[0], split, envp);
		else
		{
			perror(split[0]);
			free_path(paths);
			exit (127);
			return (-1);
		}
	}
	exec_path(paths, split, -1, save_free);
	return (1);
}

void	no_pipe_waitpid(pid_t pid, int *wstatus)
{
	int	result;

	result = waitpid(pid, wstatus, 0);
	if (result == -1 || g_error != 0)
	{
		waitpid(-1, wstatus, 0);
	}
	if (g_error == 4 || g_error == 5)
		g_error = 130;
	else if (g_error == 6)
		g_error = 131;
	else
		g_error = *wstatus >> 8;
}

int	check_cmd(t_action *action, char **envp)
{
	if (!action->cmd || !action->cmd[0])
	{
		if (g_error == 4 || g_error == 5)
			g_error = 130;
		else if (g_error == 6)
			g_error = 131;
		clear_envp(envp);
		return (0);
	}
	return (1);
}
