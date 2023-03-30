/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:48:36 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 10:38:18 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	here_doc_child(int fds[2], t_redir **redir,
	t_list **envp_lst, t_save_free **save_free)
{
	close(fds[0]);
	signal(SIGQUIT, SIG_IGN);
	here_doc_loop(redir, envp_lst, fds);
	if ((*redir)->here_doc_limiter)
		free((*redir)->here_doc_limiter);
	ft_envp_lstclear(envp_lst, free);
	free_action_elem((*save_free)->action);
	free((*save_free)->action);
	ft_word_lstclear(&(*save_free)->word_lst, free);
	ft_free_split((*save_free)->split);
	if ((*save_free)->cwd)
		free((*save_free)->cwd);
	free((*save_free)->new_line);
	free(*save_free);
	close(fds[1]);
}

/*
 **	write directly in pipe
 **	(*redir)->fd will become 'read'-fds[0] from heredoc-pipe
 */

int	write_heredoc_in_pipe(t_redir **redir, t_save_free **save_free)
{
	int		fds[2];
	int		fd_save[2];
	pid_t	pid;

	if (!redir || !(*save_free)->envp_lst)
		return (-1);
	prepare_in_out(fd_save);
	if (pipe(fds) == -1)
	{
		perror("pipe()");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		return (-1);
	}
	else if (pid == 0)
		here_doc_child(fds, redir, &(*save_free)->envp_lst, save_free);
	close(fds[1]);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		exit(1);
	wait_here_doc(pid, fd_save);
	return (fds[0]);
}

int	check_quotes_here_doc_two(const char *pipe, int i, char **limiter,
	int start)
{
	while (pipe[i] && pipe[i] != ' ' && pipe[i] != '<' && pipe[i] != '<')
		i++;
	*limiter = ft_substr(pipe, start, i - 1);
	return (i);
}

int	add_here_doc_two(t_redir **redir, t_save_free **save_free, char *limiter)
{
	struct termios	term_save;
	char			*tmp_limiter;

	if (!redir || !save_free || !limiter)
		return (-1);
	tmp_limiter = remove_start_end_quote(limiter);
	free(limiter);
	if (tmp_limiter)
		(*redir)->here_doc_limiter = ft_strdup(tmp_limiter);
	free(tmp_limiter);
	if (signal_heredoc() == 1)
		return (-1);
	tcgetattr(STDIN_FILENO, &term_save);
	(*redir)->fd = write_heredoc_in_pipe(redir, save_free);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_save);
	return (0);
}

/* skip space between << and limiter */

int	add_here_doc(t_redir **redir, const char *pipe, t_save_free **save_free,
	int *j)
{
	int		i;
	int		start;
	char	*limiter;

	i = 0;
	while (pipe[i] && pipe[i] == ' ')
		i++;
	start = i;
	i = ft_read_path(pipe, i);
	limiter = ft_substr(pipe, start, i - start);
	if (!limiter)
		return (-1);
	if (add_here_doc_two(redir, save_free, limiter) == -1)
		return (-1);
	*j += i;
	if (g_error == 5)
		return (-2);
	return (0);
}
