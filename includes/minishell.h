/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:45:52 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 14:39:36 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "parsing.h"
# include <dirent.h>
# include <termios.h>
# include <sys/stat.h>

extern int	g_error;

int		get_cwd(t_list **lst, char **cwd);
int		ft_readline_two(char **buff, t_save_free **save_free, int ret);
int		ft_readline(t_list **envp_lst, t_save_free **save_free, int ret);
void	ft_free_split(char **split);
void	init_save_free(t_save_free **save_free);

/*
 ** Signal folder
 */
int		handler_ctrl_signal(void);
void	cancel_prompt(int sig, siginfo_t *info, void *ucontext);
void	cancel_prompt_heredoc(int sig, siginfo_t *info, void *ucontext);
void	signal_backslash(int sig, siginfo_t *info, void *ucontext);

/*
 ** Environment
 */
int		expand_environment(t_list **lst, const char *env_str, char **value);
int		search_dollar(const char *env_str, int *i);
void	find_shlvl(t_list **envp_lst);
int		create_envp_lst(char **envp, t_list **envp_lst);
int		initialize_env(char **envp, t_list **envp_lst, char *cwd);
size_t	get_path_size(t_list **envp_lst);
void	ft_strlen_env(const char *s, int *i);
char	*ft_strdup_get_env(const char *s);
char	*find_dollar(char *str, t_list **envp_lst);
int		add_quotes_in_end(char **str, char **end, int i, int addition_quote);
int		search_next_dollar(const char *env_str, int *i, int *end);
char	*fuse_end_dollar(char *end, char *value, char *tmp);
int		go_to_dollar(char **str, char **end, int *len_str, int *i);
void	skip_single_quote_part_one(char **str, int *i,
			int *nb_single_quote, int *nb_double_quote);
int		skip_single_quote_part_two(char **str, char **end, int *i,
			int *len_str);
void	skip_find_quote(char **str, int *i,
			int *nb_single_quote, int *nb_double_quote);
char	*expand_exit(char *tmp, char c, int *i);
char	*find_dollar_four(t_list **envp_lst, char *str, char *value, int *i);

/*
 ** EXEC
 */
int		prepare_in_out(int fd_save[2]);
int		close_fd_save(int fd_save[2]);
char	**create_envp(t_list *envp_lst);
int		check_vars(char **split, char **envp);
int		double_check_env(char **envp, char **split, int i);
void	free_path(char **paths);
int		prepare_redir(t_action **action, int pipes);
void	exec_path(char **paths, char **split, int i, t_save_free **save_free);
int		exec_prep(t_save_free **save_free, t_list **action_t,
			t_list **envp_lst);
int		exec_data_init(t_exec **exec_data, t_list *action_t);
void	run_waitpid_two(t_wait *wait_vars);
int		execution(t_save_free **save_free, char **str, t_list **envp_lst,
			int i);
int		no_pipe(t_save_free **save_free, t_action *action, t_list **envp_lst,
			int ret);
int		free_exec(t_exec **exec_data);
int		child(t_exec *exec_data, int **fds);
void	prepare_child(t_save_free **save_free, t_exec **exec_data,
			t_list **envp_lst);
void	prep_child_two(t_save_free **save_free, t_exec **exec_data,
			t_list **envp_lst);
void	clear_envp(char **envp);
void	execution_execve(char **split, char **envp, char **paths);
int		exec_signal(void);

//heredoc:
int		get_next_line(char **line);
int		gnl_next(int fd, char **line, char *limiter, t_list **envp_lst);
void	here_doc_loop(t_redir **redir, t_list **envp_lst, int fds[2]);
void	wait_here_doc(pid_t pid, int fd_save[2]);
int		signal_heredoc(void);

/*
   EXEC NO_PIPE_TOOLS
 */

int		no_pipe_child_proc(char **split, char **envp, char **paths,
			t_save_free **save_free);
void	no_pipe_waitpid(pid_t pid, int *wstatus);
int		check_cmd(t_action *action, char **envp);

/*
 ** Builtin
 */
int		search_builtin(const char *str, t_action *action, t_list **envp_lst);
int		ft_pwd(t_list *envp_lst);
void	ft_unset_two(t_list **envp_lst, const char *tmp);
int		ft_unset(t_list **envp_lst, const char *str);
int		ft_cd(t_action **action, t_list **envp_lst);
char	*ft_cd_start(t_list **envp_lst, const char *path);
int		get_current_path(t_action **action, char **current_path,
			t_list **envp_lst);
char	*search_old(t_list **envp_lst);
int		cd_error_check(t_action *action);
int		ft_echo(const char *str, const char *option);
int		ft_env(t_list *envp_lst);
int		ft_export(t_list **envp_lst, const char *str, const char *val);
int		export_checker(const char *val);
int		export_checker_two(char **split, int i, t_list **envp_lst, int *ret);
int		ft_export_two(t_envp **elem, const char *str, int *ret);
void	parse_export_val_two(int *cpy_i, char **value, int equal_ok);
int		search_envp_two(t_envp *envp, t_envp *elem);
char	search_elem_into_envp(t_list **envp_lst, t_envp *elem);
int		parse_export_key_two(char **key, const char *str, int *i, char **tmp);
void	ft_swap(t_list **a, t_list **b);
void	ft_export_display(t_list **envp_lst);
int		ft_remove_quotes(t_envp **elem, char **mem_str, const char *str);
int		check_key_value(const char *str);
int		ft_exit(t_action **action);
void	update_pwd(t_list **envp_lst, char *current_path);
char	*update_pwd_main(t_list **envp_lst, char **current_path);
void	ft_cd_three(t_list **envp_lst, char **current_path);

/*
 ** Builtin cd tools
 */
char	*search_home(t_list **envp_lst);
char	envp_exist(t_list **envp_lst, char *str);
char	*update_old_pwd_two(t_list **envp_lst);
void	update_old_pwd_one(t_list **envp_lst);

#endif
