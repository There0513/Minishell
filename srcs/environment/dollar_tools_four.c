/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tools_four.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:13:15 by threiss           #+#    #+#             */
/*   Updated: 2022/02/08 11:38:19 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** strjoin fuse_start_dollar with env part
 */

char	*fuse_end_dollar(char *end, char *value, char *tmp)
{
	end = ft_strjoin(value, tmp);
	free(value);
	free(tmp);
	value = NULL;
	tmp = NULL;
	if (!end)
		return (NULL);
	return (end);
}
