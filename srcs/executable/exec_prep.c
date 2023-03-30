/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:20:59 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 14:37:28 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 **	pipe(fds) -> create pipe
 **	each pipe has its own fds[2]
 **	fork()	  -> create child process
 **	fd_save not necessary in prepare_child function
 ** if not last pipe -> redirect stdout to fds[1]
 */

void	prepare_child(t_save_free **save_free, t_exec **exec_data,
			t_list **envp_lst)
{
	if (!exec_data || !envp_lst || !*envp_lst)
		return ;
	if (pipe((*exec_data)->action->fds) == -1)
	{
		perror("pipe()");
		return ;
	}
	(*exec_data)->action->pid = fork();
	if ((*exec_data)->action->pid == -1)
	{
		close((*exec_data)->action->fds[0]);
		close((*exec_data)->action->fds[1]);
		perror("fork()");
	}
	else if ((*exec_data)->action->pid == 0)
		prep_child_two(save_free, exec_data, envp_lst);
	if (dup2((*exec_data)->action->fds[0], STDIN_FILENO) == -1)
		exit(1);
	close((*exec_data)->action->fds[0]);
	close((*exec_data)->action->fds[1]);
}

void	run_kill(t_list **action_t, t_wait wait_vars, int nb_pipes,
	int *wstatus)
{
	t_action	*action;

	action = NULL;
	while (nb_pipes >= wait_vars.i)
	{
		if (action_t && *action_t)
		{
			action = (*action_t)->content;
			kill(action->pid, SIGKILL);
			if ((*action_t))
				action_t = &(*action_t)->next;
		}
		waitpid(-1, wstatus, 0);
		wait_vars.i++;
	}
}

void	run_waitpid(t_list **action_t, int nb_pipes)
{
	t_action	*action;
	t_wait		wait_vars;
	int			wstatus;

	wstatus = 0;
	wait_vars.i = 0;
	wait_vars.result = 0;
	while (nb_pipes >= wait_vars.i && g_error != 5)
	{
		if (g_error == 4 || g_error == 6)
			g_error = 0;
		action = (*action_t)->content;
		wait_vars.i++;
		wait_vars.result = waitpid(action->pid, &wstatus, 0);
		run_waitpid_two(&wait_vars);
		if ((*action_t))
			action_t = &(*action_t)->next;
	}
	if (g_error == 4 || g_error == 5)
		g_error = 130;
	else if (g_error == 6)
		g_error = 131;
	else
		g_error = wstatus >> 8;
	run_kill(action_t, wait_vars, nb_pipes, &wstatus);
}

void	run_action_t(t_save_free **save_free, t_list **action_t,
			t_list **envp_lst, t_exec *exec_data)
{
	while (*action_t)
	{
		exec_data->action = (*action_t)->content;
		prepare_child(save_free, &exec_data, envp_lst);
		action_t = &(*action_t)->next;
		exec_data->pipe_actu++;
	}
}

/*
 ** prepare execution pipe by pipe
 **	prepare fd_save + close fd_save here? or in each child?
 **	handle fd_save here or in no_pipe?
*/

int	exec_prep(t_save_free **save_free, t_list **action_t, t_list **envp_lst)
{
	t_list	*beginn;
	int		fd_save[2];

	if (exec_data_init(&(*save_free)->exec_data, *action_t) != 1)
	{
		free((*save_free)->exec_data);
		return (-1);
	}
	if (exec_signal())
		return (-1);
	if ((*save_free)->exec_data->nbr_of_pipes == 0)
	{
		free((*save_free)->exec_data);
		return (no_pipe(save_free, (*action_t)->content, envp_lst, 0));
	}
	beginn = *action_t;
	prepare_in_out(fd_save);
	run_action_t(save_free, action_t, envp_lst, (*save_free)->exec_data);
	run_waitpid(action_t, (*save_free)->exec_data->nbr_of_pipes);
	close_fd_save(fd_save);
	*action_t = beginn;
	free((*save_free)->exec_data);
	return (1);
}
