/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:52:09 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/10 17:42:04 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/* write directly to stdout (fds handled before) */
int	ft_echo(const char *args_cmd, const char *option)
{
	char	*remember_str;
	int		start;
	int		cpy_start;

	if (!args_cmd && !option)
	{
		printf("\n");
		return (1);
	}
	start = loop_quotes(args_cmd);
	cpy_start = start;
	remember_str = looping_way(args_cmd, &cpy_start);
	if (!remember_str)
		return (-1);
	ft_putstr_fd(remember_str, 1);
	if (!option || ft_strcmp(option, "-n"))
		printf("\n");
	free(remember_str);
	g_error = 0;
	return (1);
}
