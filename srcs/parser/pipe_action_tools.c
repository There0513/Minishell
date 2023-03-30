/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_action_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:05:50 by threiss           #+#    #+#             */
/*   Updated: 2022/02/16 16:26:28 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_action(t_action **action)
{
	(*action)->cmd = NULL;
	(*action)->args_cmd = 0;
	(*action)->lst_redir = NULL;
}

int	free_split_return(char **split, int ret)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return (ret);
}

int	put_in_lst_three(int i, char *pipe, int start, t_action **action)
{
	char	*substr_tmp;
	char	**split;

	substr_tmp = 0;
	split = NULL;
	substr_tmp = ft_substr(pipe, start, i - start);
	if (!substr_tmp)
		return (-1);
	split = ft_split_parser(substr_tmp, ' ');
	free(substr_tmp);
	if (!split)
		return (-1);
	substr_tmp = NULL;
	check_add_simple_cmd(split, action);
	free_split_return(split, 0);
	split = NULL;
	return (1);
}

int	put_lst_loop(char *pipe, int in_word, int quote, int i)
{
	if (pipe[i] == 34)
	{
		in_word = INSIDE_DOUBLE;
		quote = i;
	}
	else if (pipe[i] == 39)
	{
		in_word = INSIDE_SINGLE;
		quote = i;
	}
	if (in_word != 0)
	{
		i++;
		while (pipe[i] && pipe[i] != pipe[quote])
			i++;
		in_word = 0;
		i++;
	}
	else
		i++;
	return (i);
}

/* 
 ** return (i) needed to ignore "error: expression result unused
 ** [-Werror,-Wunused-value]
 */
int	put_in_lst_two(int i, char *pipe, t_action **action)
{
	int		start;
	int		in_word;
	int		quote;

	start = i;
	in_word = 0;
	quote = 0;
	while (pipe[i] && pipe[i] != '<' && pipe[i] != '>')
		i = put_lst_loop(pipe, in_word, quote, i);
	if (put_in_lst_three(i, pipe, start, action) == -1)
		return (-1);
	in_word = 0;
	return (i);
}
