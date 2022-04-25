/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:19:26 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/25 19:54:46 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char ***tab, int i)
{
	int	x;

	x = 0;
	if (*tab != NULL)
	{
		while (x < i)
		{
			free((*tab)[x]);
			x++;
		}
		free((*tab)[x]);
		free(*tab);
		*tab = NULL;
	}
}

static void	exit_utils(t_tkn *tkn)
{
	if (tkn->tokens != NULL)
		free_tab(&tkn->tokens, tkn->tkn_count);
	if (tkn->lexemas != NULL)
		free_tab(&tkn->lexemas, tkn->tkn_count);
	if (tkn->line != NULL)
		free(tkn->line);
	if (tkn->logname != NULL)
		free(tkn->logname);
	if (tkn->path_0 != NULL)
		free(tkn->path_0);
	free_tab(&tkn->path, tkn->path_count);
}

void	exit_shell(t_tkn *tkn, t_cmd **cmd_tab)
{
	int		i;
	t_cmd	*swap;

	if (cmd_tab != NULL)
	{
		while (*cmd_tab!= NULL)
		{
			i = 0;
			if ((*cmd_tab)->words != NULL)
			{
				while ((*cmd_tab)->words[i] != NULL)
					i++;
				free_tab(&(*cmd_tab)->words, i);
			}
			i = 0;
			if ((*cmd_tab)->redirects != NULL)
			{
				while ((*cmd_tab)->redirects[i] != NULL)
					i++;
				free_tab(&(*cmd_tab)->redirects, i);
			}
			i = 0;
			if ((*cmd_tab)->here_docs != NULL)
			{
				while ((*cmd_tab)->here_docs[i] != NULL)
					i++;
				free_tab(&(*cmd_tab)->here_docs, i);
			}
		
		swap = *cmd_tab;
		*cmd_tab = (*cmd_tab)->next;
		free(swap);
		}
	}
	exit_utils(tkn);
}
