/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:48:02 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/28 07:58:36 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_size(t_cmd **s_cmd)
{
	int	j;

	j = 0;
	while ((*s_cmd)->words[j] != NULL)
		j++;
	return (j);
}

static int	cmd_digit(t_cmd **s_cmd)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while ((*s_cmd)->words[1][j] != '\0')
	{
		if (j == 0 && (*s_cmd)->words[1][j] != '+'
				&& (*s_cmd)->words[1][j] != '-'
				&& ft_isdigit((*s_cmd)->words[1][j]) == 1)
			flag = 1;
		if (j != 0 && ft_isdigit((*s_cmd)->words[1][j]) == 1)
			flag = 1;
		j++;
	}
	return (flag);
}

static int	not_valid_exit(t_cmd **s_cmd, int len, int is_digit)
{
	if (is_digit == 1)
	{
		setup_error((*s_cmd)->words[1], 8);
		return (1);
	}
	else if (len > 2)
	{
		setup_error((*s_cmd)->words[1], 7);
		return (1);
	}
	return (0);
}

void	exec_cmd_exit(t_cmd **s_cmd, t_tkn *tkn)
{
	int	len;
	int	is_digit;

	if ((*s_cmd)->words[1] == NULL)
		global_exit = 0;
	else
	{
		len = cmd_size(s_cmd);
		is_digit = cmd_digit(s_cmd);
		if (not_valid_exit(s_cmd, len, is_digit) == 1)
			return ;
		else
		{
			if (ft_atoi((*s_cmd)->words[1]) > 256)
				global_exit = (ft_atoi((*s_cmd)->words[1]) % 256);
			else
				global_exit = (ft_atoi((*s_cmd)->words[1]));
		}
	}
	exit_shell(tkn, s_cmd);
	free_tab(&tkn->envp, tkn->envp_count);
	rl_clear_history();
	exit(global_exit);
}
