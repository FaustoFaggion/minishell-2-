/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:54:34 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/20 16:54:50 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_path(t_tkn *tkn)
{
	int		i;
	char	**temp;

	i = -1;
	while (tkn->envp[++i] != NULL)
	{
		if (ft_strncmp("PATH=", tkn->envp[i], 5) == 0)
		{
			temp = ft_split(tkn->envp[i], '=');
			tkn->path = ft_split(temp[1], ':');
			if (tkn->path == NULL)
			{
				write(2, "ft_split error on function check\n", 33);
				return ;
			}
			free_tab(&temp, 2);
		}
	}
}

void	init_tkn(t_tkn *tkn)
{
	tkn->line = NULL;
	tkn->tokens = NULL;
	tkn->lexemas = NULL;
	tkn->cmd = NULL;
	tkn->path = NULL;
	tkn->path_0 = NULL;
	tkn->fd_in = 0;
	tkn->fd_out = 1;
	copy_path(tkn);
	tkn->path_count = 0;
	if (tkn->path != NULL)
	{
		while (tkn->path[tkn->path_count] != NULL)
			tkn->path_count++;
	}
	tkn->envp_count = 0;
	while (tkn->envp[tkn->envp_count] != NULL)
		tkn->envp_count++;
}
