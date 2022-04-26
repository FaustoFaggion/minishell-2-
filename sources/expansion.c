/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/26 13:42:44 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	s_quoted(char **tkn, int j)
{
	int	k;

	while ((*tkn)[j + 1] != '\'')
	{
		(*tkn)[j] = (*tkn)[j + 1];
		j++;
	}
	k = 0;
	while ((*tkn)[j + k + 2] != '\0')
	{
		(*tkn)[j + k] = (*tkn)[j + k + 2];
		k++;
	}
	(*tkn)[j + k] = '\0';
	return (j - 1);
}

void	expansion(t_tkn *tkn, t_cmd **cmd_tab)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	cmd = *cmd_tab;
	while (cmd != NULL)
	{
		i = 0;
		if (cmd->words != NULL)
		{
			while (cmd->words[i] != NULL)
			{
				j = 0;
				while (cmd->words[i][j] != '\0')
				{
//						exec_cmd_path_ck(tkn, i);
					if (cmd->words[i][j] == '~')
					{
						if(j == 0)
							j = expansion_tilde(tkn, &cmd->words[i], j);
					}
					else if (cmd->words[i][j] == '$')
						j = prepare_envp(&tkn, &cmd->words[i], j);
					else if (cmd->words[i][j] == '\"')
						j = prepare_quote(&tkn, &cmd->words[i], j);
					else if (cmd->words[i][j] == '\'')
						j = s_quoted(&cmd->words[i], j);
					j++;
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
}
