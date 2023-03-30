/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_to_actions_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:59:29 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/16 16:02:43 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_redir_sign_to_action(t_redir **redir)
{
	if ((*redir)->type_one == '>' && (*redir)->type_two == '>')
		(*redir)->sign = APPEND;
	else if ((*redir)->type_one == '>' && !(*redir)->type_two)
		(*redir)->sign = REDIR_OUT;
	else if ((*redir)->type_one == '<' && !(*redir)->type_two)
		(*redir)->sign = REDIR_IN;
	else if ((*redir)->type_one == '<' && (*redir)->type_two == '<')
		(*redir)->sign = HERE_DOC;
}
