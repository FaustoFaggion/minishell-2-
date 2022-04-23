/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:59:12 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/20 14:42:32 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sintax_error(t_tkn *tkn, char *token)
{
	setup_error(token, 3);
	exit_shell(tkn);
}

static int	check_cmd(t_tkn *tkn, int i, char *token)
{
	if (tkn->lexemas[++i] == NULL)
	{
		setup_error(token, 4);
		exit_shell(tkn);
		return (-1);
	}
	else
	{
		if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
			i++;
		else
		{
			setup_error(token, 5);
			exit_shell(tkn);
			return (-1);
		}
	}
	return (i);
}

static int	check_pipe(t_tkn *tkn, int i, char *token)
{
	if (tkn->lexemas[++i] == NULL || ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
	{
		sintax_error(tkn, token);
		return (-1);
	}	
	return (i);
}

static int	check_sintax(t_tkn *tkn, int i)
{
	while (tkn->lexemas[i] != NULL)
	{
		if (ft_strncmp(tkn->lexemas[i], "LESS", 4) == 0)
			i = check_cmd(tkn, i, tkn->tokens[i]);
		else if (ft_strncmp(tkn->lexemas[i], "DLESS", 5) == 0)
			i = check_cmd(tkn, i, tkn->tokens[i]);
		else if (ft_strncmp(tkn->lexemas[i], "GREAT", 5) == 0)
			i = check_cmd(tkn, i, tkn->tokens[i]);
		else if (ft_strncmp(tkn->lexemas[i], "DGREAT", 6) == 0)
			i = check_cmd(tkn, i, tkn->tokens[i]);
		else if (ft_strncmp(tkn->lexemas[i], "ASSIGNMENT_WORD", 15) == 0)
			i++;
		else if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
			i++;
		else if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
			i = check_pipe(tkn, i, tkn->tokens[i]);
		else
			break ;
		if (i == -1)
			return (1);
	}
	return (0);
}

int	sintax_analysis(t_tkn *tkn)
{
	int	i;

	i = 0;
	if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
	{
		sintax_error(tkn, tkn->tokens[i]);
		return (1);
	}
	if (check_sintax(tkn, i) == 1)
		return (1);
	return (0);
}
