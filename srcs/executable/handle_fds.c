/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:40:47 by threiss           #+#    #+#             */
/*   Updated: 2022/02/07 19:01:32 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	call this function before execution to prepare stdin stdout in case of
**	redirections
*/
int	prepare_in_out(int fd_save[2])
{
	fd_save[0] = -1;
	fd_save[1] = -1;
	fd_save[0] = dup(STDIN_FILENO);
	if (fd_save[0] < 0)
	{
		printf("fd_save[0] < 0\n");
		return (-1);
	}
	fd_save[1] = dup(STDOUT_FILENO);
	if (fd_save[1] < 0)
	{
		printf("fd_save[1] < 0\n");
		close(fd_save[0]);
		return (-1);
	}
	return (1);
}

/*
**	close fd_save at the end of the execution
*/
int	close_fd_save(int fd_save[2])
{
	if (fd_save[0] >= 0)
	{
		dup2(fd_save[0], STDIN_FILENO);
		close(fd_save[0]);
	}
	if (fd_save[1] >= 0)
	{
		dup2(fd_save[1], STDOUT_FILENO);
		close(fd_save[1]);
	}
	return (1);
}
