/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: threiss <threiss@studend.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:28:15 by gchopin           #+#    #+#             */
/*   Updated: 2022/02/08 11:09:48 by threiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_list *envp_lst)
{
	char	*pwd;
	size_t	len;

	pwd = NULL;
	len = get_path_size(&envp_lst) + 1;
	pwd = getcwd(pwd, len);
	if (!pwd)
	{
		ft_putstr_fd("Error pwd\n", 2);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}
