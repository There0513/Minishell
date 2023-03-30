/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:34:10 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 14:17:22 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error = 0;

/*
 **	transform output newline (touch enter) into a carriage return
 **	output post processing, with ONLCR, it cause an extra carriage return
 **	so it prevent odd tabulation in raw mode
 **	control special character with CTRL
 */

void	init_termios(struct termios *term_save)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, term_save);
	tcgetattr(STDIN_FILENO, &term);
	term.c_oflag |= ONLCR;
	term.c_oflag |= OPOST;
	term.c_cc[VEOF] = 4;
	term.c_cc[VINTR] = 3;
	term.c_cc[VQUIT] = 034;
	term.c_lflag = ISIG | ICANON | ECHO | ECHOE | ECHOK | ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

int	init_shell(t_list **envp_lst, struct termios *term_save
		, char **envp, char **cwd)
{
	int	signal_handler;

	init_termios(term_save);
	if (initialize_env(envp, envp_lst, *cwd))
		return (1);
	signal_handler = handler_ctrl_signal();
	if (signal_handler != 0)
		return (signal_handler);
	if (get_cwd(envp_lst, cwd))
		return (1);
	if (!*cwd)
	{
		ft_envp_lstclear(envp_lst, free);
		return (1);
	}
	return (0);
}

int	bye_bye(t_save_free **save_free, t_list **envp_lst,
	struct termios *term_save)
{
	if ((*save_free)->cwd)
		free((*save_free)->cwd);
	ft_envp_lstclear(envp_lst, free);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, term_save);
	free(*save_free);
	return (1);
}

void	clear_free_envp_save(char **cwd, t_list **envp_lst,
	t_save_free *save_free)
{
	if (*cwd)
	{
		free(*cwd);
		*cwd = NULL;
	}
	if (envp_lst)
		ft_envp_lstclear(envp_lst, free);
	free(save_free);
}

int	main(int ac, char **av, char **envp)
{
	t_save_free		*save_free;
	struct termios	term_save;
	t_list			*envp_lst;
	char			*cwd;
	int				result_init;

	(void)ac;
	(void)av;
	cwd = NULL;
	envp_lst = NULL;
	result_init = init_shell(&envp_lst, &term_save, envp, &cwd);
	if (result_init)
		return (result_init);
	save_free = malloc(sizeof(t_save_free));
	init_save_free(&save_free);
	save_free->cwd = cwd;
	save_free->envp_lst = envp_lst;
	if (!save_free)
		return (-1);
	if (!ft_readline(&envp_lst, &save_free, 0))
		return (bye_bye(&save_free, &envp_lst, &term_save));
	clear_free_envp_save(&cwd, &envp_lst, save_free);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_save);
	printf("exit\n");
	return (0);
}
