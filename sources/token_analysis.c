/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:10:30 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/19 10:09:25 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	metachar_check(t_tkn *tkn, int i)
{
	if (tkn->line[i] == '|')
		i++;
	else if (tkn->line[i] == '<')
	{
		i++;
		if (tkn->line[i] == '<')
			i++;
	}
	else if (tkn->line[i] == '>')
	{
		i++;
		if (tkn->line[i] == '>')
			i++;
		if (tkn->line[i] == '|')
			i++;
	}
	return (i);
}

static int	quotes_check(t_tkn *tkn, int i, char c)
{
	i++;
	while (tkn->line[i] != c)
	{
		if (tkn->line[i] == '\0')
		{
			exit_shell_quote(tkn, tkn->tkn_count);
			setup_error(&tkn->line[i], 2);
			return (-1);
		}
		i++;
	}	
	i++;
	return (i);
}

int	token_count(t_tkn *tkn)
{
	int	i;

	i = 0;
	tkn->tkn_count = 0;
	while (tkn->line[i] != '\0')
	{
		while (tkn->line[i] == ' ' && tkn->line[i] != '\0')
			i++;
		if (tkn->line[i] != '\0')
		{
			if (ft_strchr("|<>", tkn->line[i]) != NULL)
				i = metachar_check(tkn, i);
			else
			{
				while (ft_strchr("|<> ", tkn->line[i]) == NULL)
				{
					if (tkn->line[i] == '\'' || tkn->line[i] == '\"')
					{
						i = quotes_check(tkn, i, tkn->line[i]);
						if (i == -1)
							return (1);
					}
					else
						i++;
				}
			}
			tkn->tkn_count++;
		}
	}
	return (0);
}

static void	scan_cmd_line(t_tkn *tkn)
{
	int	i;
	int	x;
	int	start;

	i = 0;
	x = 0;
	while (tkn->line[i] != '\0')
	{
		while (tkn->line[i] == ' ' && tkn->line[i] != '\0')
			i++;
		if (tkn->line[i] != '\0')
		{
			start = i;
			if (ft_strchr("|<>", tkn->line[i]) != NULL)
				i = metachar_check(tkn, i);
			else
			{
				while (ft_strchr("|<> ", tkn->line[i]) == NULL)
				{
					if (tkn->line[i] == '\'' || tkn->line[i] == '\"')
						i = quotes_check(tkn, i, tkn->line[i]);
					else
						i++;
				}
			}
			tkn->len = i - start;
			tkn->tokens[x] = ft_substr(tkn->line, start, tkn->len);
			x++;
		}
	}
	tkn->tokens[x] = NULL;
}

int	token_analysis(t_tkn *tkn)
{
	int	probl;

	probl = token_count(tkn);
	if (probl == 1)
		return (1);
	tkn->tokens = (char **) malloc(sizeof(char *) * (tkn->tkn_count + 1));
	if (!tkn->tokens)
		return (1);
	scan_cmd_line(tkn);
	return (0);
}
