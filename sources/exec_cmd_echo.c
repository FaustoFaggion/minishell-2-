/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:06:35 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/28 08:11:56 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_echo(t_cmd **s_cmd)
{
	int	j;

	j = 1;
	if ((*s_cmd)->words[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp((*s_cmd)->words[1], "-n", 2) == 0)
		j = 2;
	while ((*s_cmd)->words[j] != NULL)
	{
		printf("%s ", (*s_cmd)->words[j]);
		j++;
	}
	if (ft_strncmp((*s_cmd)->words[1], "-n", 2) != 0)
		printf("\n");
	return ;
}
