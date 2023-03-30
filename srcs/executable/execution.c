/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:17:41 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 13:14:17 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_path_two(char **paths, char **envp, char **split, int i)
{
	char	*path_tmp;
	char	*new_path;
	char	*tmp;

	tmp = ft_substr(paths[i], 5, ft_strlen(paths[i]));
	if (tmp)
	{
		free(paths[i]);
		paths[i] = tmp;
		while (paths[i])
		{
			path_tmp = ft_strjoin(paths[i], "/");
			if (path_tmp == 0)
				return ;
			new_path = ft_strjoin(path_tmp, split[0]);
			if (new_path == 0)
				return ;
			if (access(new_path, F_OK) == 0)
				execve(new_path, split, envp);
			free(path_tmp);
			free(new_path);
			i++;
		}
	}
}

/*
**	Exit code 127 means job's command can not be found or executed.
*/
void	exec_path(char **paths, char **split, int i, t_save_free **save_free)
{
	i++;
	exec_path_two(paths, (*save_free)->envp_var, split, i);
	ft_putstr_fd(split[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_path(paths);
	ft_free_split((*save_free)->envp_var);
	ft_envp_lstclear(&(*save_free)->envp_lst, free);
	ft_action_t_lstclear((*save_free)->action_t, free);
	free((*save_free)->cwd);
	free((*save_free)->new_line);
	if ((*save_free)->word_lst)
		ft_word_lstclear(&(*save_free)->word_lst, free);
	if ((*save_free)->pipes != 0 && (*save_free)->exec_data != NULL)
		free((*save_free)->exec_data);
	free(*save_free);
	exit(127);
}

int	check_vars(char **split, char **envp)
{
	if (split == 0)
		return (-1);
	if (split[0] == 0)
	{
		ft_putstr_fd("command not found _check_vars\n", 2);
		free(split);
		return (-1);
	}
	if (envp[0] == NULL)
	{
		ft_putstr_fd(split[0], 2);
		ft_putstr_fd(": command not found _check_vars\n", 2);
		return (-1);
	}
	return (1);
}

void	execution_execve(char **split, char **envp, char **paths)
{
	struct stat	sb;

	if (split[0][0] == '/' || (split[0][0] == '.' && split[0][1] == '/')
		|| stat(split[0], &sb) == 0)
	{
		if (access(split[0], F_OK) == 0)
			execve(split[0], split, envp);
		else
		{
			perror(split[0]);
			clear_envp(envp);
			free_path(paths);
			exit (127);
		}
	}
}

/*
 **	find PATH in env + check if paths/cmd exists
 ** clear_envp(envp) at the end ?! not needed
*/
int	execution(t_save_free **save_free, char **split, t_list **envp_lst, int i)
{
	char	**paths;
	char	**envp;

	envp = NULL;
	if (envp_lst && *envp_lst)
		envp = create_envp(*envp_lst);
	if (check_vars(split, envp) == -1)
		return (-1);
	(*save_free)->envp_var = envp;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	if (double_check_env(envp, split, i) != 1)
		return (-1);
	paths = ft_split(envp[i], ':');
	if (paths == 0)
		return (-1);
	execution_execve(split, envp, paths);
	exec_path(paths, split, -1, save_free);
	return (1);
}
