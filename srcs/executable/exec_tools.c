/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:18:40 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 14:37:45 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prep_child_two(t_save_free **save_free, t_exec **ex_d,
			t_list **envp_lst)
{
	close((*ex_d)->action->fds[0]);
	if ((*ex_d)->pipe_actu < (*ex_d)->nbr_of_pipes)
	{
		if (dup2((*ex_d)->action->fds[1], STDOUT_FILENO) == -1)
			exit(1);
		close((*ex_d)->action->fds[1]);
	}
	prepare_redir(&(*ex_d)->action, 1);
	if (!(*ex_d)->action->cmd)
		exit(1);
	if (search_builtin((*ex_d)->action->cmd[0], (*ex_d)->action, envp_lst) == 0)
		execution(save_free, (*ex_d)->action->cmd, envp_lst, 0);
	close((*ex_d)->action->fds[1]);
	if ((*save_free)->envp_var)
		ft_free_split((*save_free)->envp_var);
	(*save_free)->envp_var = NULL;
	ft_envp_lstclear(&(*save_free)->envp_lst, free);
	ft_action_t_lstclear((*save_free)->action_t, free);
	free((*save_free)->cwd);
	free((*save_free)->new_line);
	if ((*save_free)->word_lst)
		ft_word_lstclear(&(*save_free)->word_lst, free);
	free((*save_free)->exec_data);
	free(*save_free);
	exit(g_error);
}

void	run_waitpid_two(t_wait *wait_vars)
{
	int	wstatus;

	wstatus = 0;
	if (wait_vars->result == -1)
	{
		waitpid(-1, &wstatus, 0);
	}
}

int	exec_data_init(t_exec **exec_data, t_list *action_t)
{
	if (!action_t)
		return (-1);
	*exec_data = malloc(sizeof(t_exec));
	if (!*exec_data)
		return (-1);
	(*exec_data)->action = NULL;
	(*exec_data)->nbr_of_pipes = ft_lstsize(action_t) - 1;
	(*exec_data)->pipe_actu = 0;
	return (1);
}

int	exec_signal(void)
{
	struct sigaction	s_sig_one;
	struct sigaction	s_sig_two;
	int					result;

	ft_memset(&s_sig_one, 0, sizeof(struct sigaction));
	ft_memset(&s_sig_two, 0, sizeof(struct sigaction));
	s_sig_one.sa_flags = SA_SIGINFO | SA_NODEFER;
	s_sig_two.sa_flags = SA_SIGINFO | SA_NODEFER;
	s_sig_one.sa_sigaction = cancel_prompt;
	s_sig_two.sa_sigaction = signal_backslash;
	result = sigaction(SIGINT, &s_sig_one, NULL);
	if (result < 0)
	{
		perror("Error ");
		return (1);
	}
	result = sigaction(SIGQUIT, &s_sig_two, NULL);
	if (result < 0)
	{
		perror("Error ");
		return (1);
	}
	return (0);
}
