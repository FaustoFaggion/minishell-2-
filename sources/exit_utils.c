/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:08:22 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/20 10:08:34 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_path(t_tkn *tkn)
{
	int	x;

	x = 0;
	if (tkn->path != NULL)
	{
		while (x < tkn->path_count)
		{
			free(tkn->path[x]);
			x++;
		}
		free(tkn->path);
		tkn->path = NULL;
	}
}

void	exit_shell_quote(t_tkn *tkn, int i)
{
	int	x;

	x = 0;
	if (tkn->tokens != NULL)
	{
		while (x < i)
		{
			free(tkn->tokens[x]);
			x++;
		}
		free(tkn->tokens);
	}
	x = 0;
	if (tkn->lexemas != NULL)
	{
		while (x < tkn->tkn_count)
		{
			free(tkn->lexemas[x]);
			x++;
		}
		free(tkn->lexemas);
	}
	if (tkn->line != NULL)
		free(tkn->line);
	free_path(tkn);
}
