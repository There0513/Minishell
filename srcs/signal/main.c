/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:28:45 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/17 13:13:53 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_prompt(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
	{
		if (info->si_pid != 0)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_error = 130;
		}
	}
}

void	cancel_prompt(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
	{
		if (info->si_pid == 0)
		{
			ft_putstr_fd("\n", 1);
			if (g_error == 0)
				g_error = 4;
		}
	}
}

void	cancel_prompt_heredoc(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
	{
		if (info->si_pid == 0)
		{
			ft_putstr_fd("^C\n", 1);
			g_error = 5;
		}
	}
}

void	signal_backslash(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGQUIT)
	{
		if (info->si_pid == 0)
		{
			ft_putstr_fd("Quit (Core dumped)\n", 2);
			g_error = 6;
		}
	}
}

int	handler_ctrl_signal(void)
{
	struct sigaction	s_sigaction;
	struct sigaction	s_sigaction_two;
	int					result;

	ft_memset(&s_sigaction, 0, sizeof(struct sigaction));
	ft_memset(&s_sigaction_two, 0, sizeof(struct sigaction));
	s_sigaction.sa_flags = SA_SIGINFO | SA_NODEFER;
	s_sigaction_two.sa_flags = SA_SIGINFO | SA_NODEFER;
	s_sigaction.sa_sigaction = new_prompt;
	s_sigaction_two.sa_handler = SIG_IGN;
	result = sigaction(SIGINT, &s_sigaction, NULL);
	if (result < 0)
	{
		perror("Error ");
		return (1);
	}
	result = sigaction(SIGQUIT, &s_sigaction_two, NULL);
	if (result < 0)
	{
		perror("Error ");
		return (1);
	}
	return (0);
}
