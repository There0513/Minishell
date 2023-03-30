/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:50:27 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 11:36:59 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"
# include "minishell.h"

void	display_split(char **str);
int		free_split_return(char **split, int ret);
int		minishell(char *line, t_save_free **save_free);
void	ft_envp_lstclear(t_list **lst, void (*del)(void *));
void	ft_word_lstclear(t_list **lst, void (*del)(void *));
void	init_action(t_action **action);
int		put_in_lst_two(int i, char *pipe, t_action **action);
void	ft_action_t_lstclear(t_list **lst, void (*del)(void *));
t_redir	*check_add_redirections(const char *pipe, int *i, t_list **envp_lst,
			t_save_free **save_free);
char	**ft_split_parser(char const *s, char c);
int		error_check(t_list **word_lst, char *str);
int		add_here_doc(t_redir **redir, const char *pipe,
			t_save_free **save_free, int *i);
int		init_redir(t_redir **redir, const char *pipe, int *i);
int		check_quotes_here_doc(const char *pipe, int *i);
int		check_in_word(char **str, int *i, int *in_word, int *sec_quote_found);
int		check_out_word(char **str, int *i, int *in_word, int *sec_quote_found);
void	free_action_elem(t_action *action);
void	add_redir_sign_to_action(t_redir **redir);
void	simple_parse_cmd(t_action **action);
int		check_echo_option(char *str, char **tmp_cmd);

/*
 ** TOKEN
*/

int		create_token_lst(t_list **word_lst, char **str);
int		check_add_word(char **str, t_list **word_lst);
void	check_loop_word(char **str, int *i, int *in_word,
			int *sec_quote_found);
int		check_add_special_signs(char **str, t_list **word_lst);
int		add_elem_in_word(t_list **word_lst, t_token **token);
char	*add_red_left(char **str);
char	*add_red_right(char **str);
int		check_add_special_signs(char **str, t_list **word_lst);

/*
 ** TOOLS
*/

char	*find_dollar(char *str, t_list **envp_lst);
void	print_t_token(t_token *token);
int		is_spec_sign(char c);
int		pipe_to_actions_t(char *str, t_list **envp_lst, t_list **action_t,
			t_save_free **save_free);
int		is_file(char *str);
int		check_add_simple_cmd(char **split, t_action **action);
int		check_add_simple_cmd_two(t_action **action, char **split,
			char *tmp_cmd, int *i);
int		loop_tmp_cmd(t_action **action, char **split, char **tmp_cmd, int *i);

/*
 ** REDIRECTION
*/

char	*loop_remove_quote(const char *str, char *new, int *j);
char	*looping_way(const char *str, int *j);
char	*join_no_quote(const char *str, char *new, int *j);
char	*inside_loop(const char *str, char *new, int *j);
int		check_redirection_one(const char *pipe, int *i);
int		check_redirection_two(const char *pipe, int *j);
int		ft_read_inside(const char *pipe, int *i, int *in_word,
			int *sec_quote_found);
int		ft_read_outside(const char *pipe, int i, int *in_word,
			int *sec_quote_found);
void	open_path(t_redir **redir, const char *tmp);
int		loop_quotes(const char *str);
char	*remove_start_end_quote(const char *str);
int		get_path(t_redir **redir, const char *pipe, int i, int j);
int		ft_read_path(const char *pipe, int i);
int		check_redir_part_two(t_redir **redir, const char *pipe, int *i, int *j);
int		check_redir_part_three(t_redir **redir, const char *pipe,
			int *i, int *j);
int		check_add_three(t_redir **redir, const char *pipe,
			t_save_free **save_free, int *i);
int		check_add_two(t_redir **redir, const char *pipe,
			t_save_free **save_free, int *i);

#endif
