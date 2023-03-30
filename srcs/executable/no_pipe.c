/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:49:32 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 14:39:56 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prep_exec_two(char **paths, char **envp, char **split,
		t_save_free **save_free)
{
	pid_t	pid;

	(*save_free)->pipes = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("fork()");
		free_path(paths);
		return (-1);
	}
	else if (pid == 0)
	{
		if (no_pipe_child_proc(split, envp, paths, save_free) == -1)
			return (-1);
	}
	return (pid);
}

/*
	find PATH in env + check if paths/cmd exists
*/
int	prep_exec_no_pipe(t_action **action, char **split, int i,
		t_save_free **s)
{
	char	**paths;
	pid_t	pid;
	int		wstatus;

	if (!action || !split || !(*s)->envp_var)
		return (-1);
	wstatus = 0;
	if (check_vars(split, (*s)->envp_var) == -1)
		return (-1);
	while ((*s)->envp_var[i] && ft_strncmp((*s)->envp_var[i], "PATH", 4) != 0)
		i++;
	if (double_check_env((*s)->envp_var, split, i) != 1)
		return (-1);
	paths = ft_split((*s)->envp_var[i], ':');
	if (paths == 0)
		return (-1);
	pid = prep_exec_two(paths, (*s)->envp_var, split, s);
	if (pid < 0)
	{
		free_path(paths);
		return (-1);
	}
	free_path(paths);
	no_pipe_waitpid(pid, &wstatus);
	return (1);
}

/*
 change fds for each redirection:
 ex. ls < srcs > file redir[0] "< srcs" + redir[1] "> file"
*/

int	prepare_redir(t_action **action, int pipes)
{
	t_list	*lst_redir;
	t_redir	*redir;
	int		new_dup;

	(void)pipes;
	if (action && *action)
	{
		lst_redir = (*action)->lst_redir;
		while (lst_redir)
		{
			redir = lst_redir->content;
			if (redir->sign == REDIR_OUT || redir->sign == APPEND)
				new_dup = dup2(redir->fd, STDOUT_FILENO);
			else
				new_dup = dup2(redir->fd, STDIN_FILENO);
			if (redir->fd > 2)
				close(redir->fd);
			if (new_dup < 0)
				printf("error new_dup\n");
			lst_redir = lst_redir->next;
		}
	}
	return (1);
}

int	no_pipe_two(t_action **action, int fd_save[2], int ret,
		t_save_free **save_free)
{
	if (ret != 1 && action && *action)
		ret = prep_exec_no_pipe(action, (*action)->cmd, 0, save_free);
	close_fd_save(fd_save);
	clear_envp((*save_free)->envp_var);
	(*save_free)->envp_var = NULL;
	return (ret);
}

/*
 prepare stdin stdout -> fd_save
 if redir -> change fds with dup2
	no_pipe can be:
	- builtin or
	- bin/ cmd
  need to handle ./executable?! if "./" -> "/bin/bash"
*/

int	no_pipe(t_save_free **save_free, t_action *action, t_list **envp_lst,
	int ret)
{
	char	**envp;
	int		fd_save[2];

	envp = NULL;
	if (!envp_lst || !*envp_lst)
		return (-1);
	envp = create_envp(*envp_lst);
	if (!action)
		return (-1);
	if (!check_cmd(action, envp))
		return (0);
	(*save_free)->envp_var = envp;
	prepare_in_out(fd_save);
	prepare_redir(&action, 0);
	ret = search_builtin(action->cmd[0], action, envp_lst);
	if (ret == -1)
	{
		clear_envp(envp);
		envp = NULL;
		return (-1);
	}
	ret = no_pipe_two(&action, fd_save, ret, save_free);
	(*save_free)->pipes = 100;
	return (ret);
}
