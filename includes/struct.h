/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:34:10 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 10:55:31 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <error.h>

# define    PIPE    1   // | 
# define    APPEND  2   // >>
# define    REDIR_IN      3   // <
# define    REDIR_OUT     4   // >
# define    HERE_DOC     5   // <<

# define    INSIDE_SINGLE   6   // '    39
# define    INSIDE_DOUBLE   7   // "    34

typedef struct s_envp
{
	char	*key;
	char	*value;
}			t_envp;

typedef struct s_token
{
	char	*str;
	int		spec_sign;
}		t_token;

typedef struct s_redir
{
	int		fd;
	char	type_one;
	char	type_two;
	int		sign;
	char	*here_doc_limiter;
	int		fd_heredoc;
	char	*filename;
}		t_redir;

typedef struct s_action
{
	t_list	*lst_redir;
	char	**cmd;
	char	*args_cmd;
	int		pid;
	int		fds[2];
	int		fd_save[2];
}		t_action;

typedef struct s_exec
{
	t_action	*action;
	int			nbr_of_pipes;
	int			pipe_actu;
}		t_exec;

typedef struct s_wait
{
	int		i;
	int		result;
	int		back;
}		t_wait;

typedef struct s_save_free
{
	char		*cwd;
	t_action	*action;
	t_list		**action_t;
	t_list		*envp_lst;
	char		**envp_var;
	t_list		*word_lst;
	char		*new_line;
	char		**split;
	t_exec		*exec_data;
	int			pipes;
	t_redir		*redir;
}		t_save_free;

#endif
