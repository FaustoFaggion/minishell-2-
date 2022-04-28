/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:09:47 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/20 10:33:10 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static int	validate_var(char *cmd_arg)
{
	int	x;

	if (ft_isdigit(cmd_arg[0]) == 0)
	{
		global_exit = 1;
		return (1);
	}
	else if (ft_strncmp(cmd_arg, "=", 1) == 0)
	{
		global_exit = 0;
		return (1);
	}
	x = 0;
	while (cmd_arg[x] != '\0')
	{
		if (cmd_arg[x] == '=')
			return (0);
		x++;
	}
	return (1);
}
*/
static void	unset_var(char ***envp, char *var, int *count)
{
	char	**temp;
	int		x;
	int		y;

	temp = (char **)malloc((*count) * sizeof(char *));
	x = 0;
	y = 0;
	while ((*envp)[x + y] != NULL)
	{
		if (ft_strncmp((*envp)[x + y], var, ft_strlen(var)) == 0)
			y++;
		else
		{
			temp[x] = ft_strdup((*envp)[x + y]);
			x++;
		}
	}
	temp[x] = NULL;
	free_tab(envp, *count);
	*envp = temp;
	(*count)--;
}

void	exec_cmd_unset(char ***envp, char *cmd_arg, int *count)
{
	int		x;
	int		flag;
	char	*var;

	flag = 0;
	x = 0;
//	if (validate_var(cmd_arg) == 1)
//		printf("bash: unset: `%s`: não é um identificador válido\n", cmd_arg);
	var = ft_strjoin(cmd_arg, "=");
	while ((*envp)[x] != NULL)
	{
		if (ft_strncmp((*envp)[x], var,
			ft_strlen(var)) == 0)
			flag = 1;
		x++;
	}
	if (flag == 1)
		unset_var(envp, var, count);
	free(var);
}
