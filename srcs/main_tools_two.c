/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 22:06:43 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 11:17:56 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_save_free(t_save_free **save_free)
{
	(*save_free)->action = NULL;
	(*save_free)->action_t = NULL;
	(*save_free)->envp_var = NULL;
	(*save_free)->word_lst = NULL;
	(*save_free)->new_line = NULL;
	(*save_free)->split = NULL;
	(*save_free)->exec_data = NULL;
	(*save_free)->pipes = -1;
	(*save_free)->redir = NULL;
}
