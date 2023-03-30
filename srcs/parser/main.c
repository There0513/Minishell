/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:53:06 by threiss           #+#    #+#             */
/*   Updated: 2022/02/17 14:18:46 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	minishell_clear(t_list **word_lst, t_list **action_t, char **new_line)
{
	if (new_line && *new_line)
		free(*new_line);
	if (word_lst && *word_lst)
		ft_word_lstclear(word_lst, free);
	if (action_t && *action_t)
		ft_action_t_lstclear(action_t, free);
}

int	minishell_two(t_list **envp_lst, t_list **word_lst,
	char **line, char **new_line)
{
	int	ret;

	ret = 1;
	if (!line || !*line || !new_line || !envp_lst || !word_lst)
		return (-1);
	*new_line = find_dollar(*line, envp_lst);
	if (!*new_line)
		return (-1);
	g_error = 0;
	*line = *new_line;
	ret = error_check(word_lst, *line);
	if (ret != 1)
	{
		free(*new_line);
		*new_line = NULL;
		ft_word_lstclear(word_lst, free);
		return (ret);
	}
	return (1);
}

void	mini_two(void)
{
	if (g_error == 4 || g_error == 5)
		g_error = 130;
	else if (g_error == 6)
		g_error = 131;
}

int	minishell(char *line, t_save_free **save)
{
	t_list	*action_t;
	int		ret;

	(*save)->word_lst = NULL;
	action_t = NULL;
	if (!(*save)->envp_lst)
		return (-1);
	ret = minishell_two(&(*save)->envp_lst, &(*save)->word_lst,
			&line, &(*save)->new_line);
	if (ret != 1)
		return (ret);
	ret = pipe_to_actions_t(line, &(*save)->envp_lst, &action_t, save);
	if (ret == -1)
	{
		free((*save)->new_line);
		ft_word_lstclear(&(*save)->word_lst, free);
		return (-1);
	}
	mini_two();
	(*save)->action_t = &action_t;
	if (ret > 0)
		exec_prep(save, &action_t, &(*save)->envp_lst);
	minishell_clear(&(*save)->word_lst, &action_t,
		&(*save)->new_line);
	return (ret);
}
