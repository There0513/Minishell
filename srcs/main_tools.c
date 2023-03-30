/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:02:01 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/17 10:38:39 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cwd(t_list **lst, char **cwd)
{
	char	*tmp;

	tmp = NULL;
	if (!cwd)
		return (1);
	tmp = getcwd(tmp, get_path_size(lst) + 1);
	if (!tmp)
	{
		perror("Error ");
		return (1);
	}
	*cwd = ft_strdup(tmp);
	free(tmp);
	if (!*cwd)
		return (1);
	tmp = ft_strjoin("\033[32;1m ", *cwd);
	free(*cwd);
	*cwd = ft_strjoin(tmp, "$> \033[0m");
	free(tmp);
	if (!*cwd)
	{
		free(*cwd);
		return (1);
	}
	return (0);
}

int	ft_readline_three(t_save_free **save_free, char **buff)
{
	int	ret;

	if ((*save_free)->cwd)
	{
		free((*save_free)->cwd);
		(*save_free)->cwd = NULL;
	}
	if (buff && *buff && ft_strlen(*buff))
	{
		add_history(*buff);
		rl_on_new_line();
		ret = minishell(*buff, save_free);
		if (ret == -2)
			g_error = 2;
		if (ret == -1)
		{
			if (buff && *buff)
				free(*buff);
			return (-1);
		}
	}
	return (1);
}

int	ft_readline_two(char **buff, t_save_free **save_free, int ret)
{
	int	signal_handler;

	if (!buff)
		return (0);
	signal_handler = handler_ctrl_signal();
	if (signal_handler != 0)
		return (signal_handler);
	*buff = readline((*save_free)->cwd);
	if (*buff && ft_strlen(*buff))
	{
		add_history(*buff);
		rl_on_new_line();
		ret = minishell(*buff, save_free);
		if (ret == -2)
			g_error = 2;
		if (ret == -1 || ret == 0)
		{
			add_history(*buff);
			rl_on_new_line();
			free(*buff);
			return (ret);
		}
	}
	return (1);
}

int	ft_read_two(t_list **envp_lst, t_save_free **save_free, int ret,
	char **buff)
{
	if (get_cwd(envp_lst, &(*save_free)->cwd))
		return (0);
	if (ret != 0)
		free(*buff);
	return (1);
}

int	ft_readline(t_list **envp_lst, t_save_free **save_free, int ret)
{
	char	*buff;
	int		mem_errno;
	int		signal_handler;

	if (!envp_lst)
		return (0);
	mem_errno = g_error;
	ret = ft_readline_two(&buff, save_free, 0);
	if (ret == -1)
		return (0);
	while (buff)
	{
		signal_handler = handler_ctrl_signal();
		if (signal_handler != 0)
			return (signal_handler);
		if (ft_read_two(envp_lst, save_free, ret, &buff) == 0)
			return (0);
		mem_errno = g_error;
		buff = readline((*save_free)->cwd);
		if (ft_readline_three(save_free, &buff) == -1)
			return (0);
	}
	free(buff);
	return (1);
}
