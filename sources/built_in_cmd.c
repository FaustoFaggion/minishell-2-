/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:08:07 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/28 07:50:57 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in_utils(t_cmd **s_cmd, t_tkn *tkn)
{
	if (ft_strncmp((*s_cmd)->words[0], "export\0", 7) == 0)
	{
		exec_cmd_export(s_cmd, tkn);
		return (0);
	}
	else if (ft_strncmp((*s_cmd)->words[0], "unset\0", 6) == 0)
	{
		exec_cmd_unset(&tkn->envp, (*s_cmd)->words[1], &tkn->envp_count);
		return (0);
	}
/*	else if (ft_strncmp((*s_cmd)->words[0], "env\0", 4) == 0)
	{
		if (tkn->cmd[i][1] == NULL)
			exec_cmd_env(tkn, 0);
		return (0);
	}
*/	else if (ft_strncmp((*s_cmd)->words[0], "exit\0", 5) == 0)
	{
		exec_cmd_exit(s_cmd, tkn);
		return (0);
	}

	return (1);
}

int	built_in_cmd(t_cmd **s_cmd, t_tkn *tkn)
{
	int	ret;

	ret = 0;
/*	if (ft_strncmp((*s_cmd)->words[0], "echo\0", 5) == 0)
	{
		exec_cmd_echo(tkn, i);
		return (ret);
	}
	else if (ft_strncmp((*s_cmd)->words[0], "pwd\0", 4) == 0)
	{
		exec_cmd_pwd();
		return (ret);
	}
*/	if (ft_strncmp((*s_cmd)->words[0], "cd\0", 3) == 0)
	{
		exec_cmd_cd(s_cmd, tkn);
		return (ret);
	}
	else
	{
		ret = built_in_utils(s_cmd, tkn);
		return (ret);
	}
	return (1);
}
