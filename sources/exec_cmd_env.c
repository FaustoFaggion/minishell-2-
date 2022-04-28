/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:10:58 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/31 14:50:36 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_env(t_tkn *tkn, int flag)
{
	int	i;

	i = 0;
	if (flag == 0)
	{
		while (tkn->envp[i] != NULL)
		{
			printf("%s\n", tkn->envp[i]);
			i++;
		}
	}
	if (flag == 1)
	{
		while (tkn->envp[i] != NULL)
		{
			printf("declare -x %s\n", tkn->envp[i]);
			i++;
		}
	}
}
