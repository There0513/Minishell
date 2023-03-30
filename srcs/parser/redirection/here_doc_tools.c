/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:44:20 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 10:31:14 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_here_doc(const char *pipe, int *i)
{
	int		quotes;

	quotes = 0;
	if (pipe[*i] && pipe[*i] != 34 && pipe[*i] != 39)
		return (0);
	if (pipe[*i] && pipe[*i] == 34)
		quotes = INSIDE_DOUBLE;
	else if (pipe[*i] && pipe[*i] == 39)
		quotes = INSIDE_SINGLE;
	if (pipe[*i] && (pipe[*i] == 39 || pipe[*i] == 34))
		*i += 1;
	while (pipe[*i] && ((quotes == INSIDE_SINGLE && pipe[*i] != 39)
			|| (quotes == INSIDE_DOUBLE && pipe[*i] != 34)))
		*i += 1;
	*i -= 1;
	return (1);
}

int	signal_heredoc(void)
{
	struct sigaction	s_sig_one;
	struct sigaction	s_sig_two;
	int					result;

	ft_memset(&s_sig_one, 0, sizeof(struct sigaction));
	ft_memset(&s_sig_two, 0, sizeof(struct sigaction));
	s_sig_one.sa_flags = SA_SIGINFO | SA_NODEFER;
	s_sig_two.sa_flags = SA_SIGINFO | SA_NODEFER;
	s_sig_one.sa_sigaction = cancel_prompt_heredoc;
	s_sig_two.sa_handler = SIG_IGN;
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

void	wait_here_doc(pid_t pid, int fd_save[2])
{
	int	result;
	int	wstatus;

	result = 0;
	wstatus = 0;
	result = waitpid(pid, &wstatus, WNOHANG);
	if (result == -1)
	{
		if (g_error == 5)
			g_error = 5;
	}
	while (result == 0 && g_error != 5)
		result = waitpid(pid, &wstatus, WNOHANG);
	close_fd_save(fd_save);
	if (g_error == 5)
	{
		kill(pid, SIGKILL);
		waitpid(-1, &wstatus, 0);
	}
}

void	here_doc_loop(t_redir **redir, t_list **envp_lst, int fds[2])
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	line = readline(NULL);
	while (line)
	{
		tmp = ft_strjoin(line, "\n");
		if (line)
			free(line);
		line = ft_strdup(tmp);
		if (gnl_next(fds[1], &line, (*redir)->here_doc_limiter,
				envp_lst) == 0)
			break ;
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		line = readline(NULL);
	}
	if (tmp)
		free(tmp);
}
