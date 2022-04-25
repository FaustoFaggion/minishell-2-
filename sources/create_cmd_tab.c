/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:51:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/25 20:02:16 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_cmd_tab(t_cmd *cmd_tab)
{
	int		stop;
	int		i;
	t_cmd	*s_cmd;
	int		x;
	
	s_cmd = cmd_tab;
	stop = 0;
	x = 0;
	while (stop == 0)
	{
		i = 0;
		printf ("s_cmd[%d]->words = ", x);
		if (s_cmd->words != NULL)
		{
			while (s_cmd->words[i] != NULL)
			{
				printf ("%s  ", s_cmd->words[i]);
				i++;
			}
			printf ("%s  ", s_cmd->words[i]);
		}
			printf ("\n");
			i = 0;
			printf ("s_cmd[%d]->redirects = ", x);
		if (s_cmd->redirects != NULL)
		{
			while (s_cmd->redirects[i] != NULL)
			{
				printf ("%s  ", s_cmd->redirects[i]);
				i++;
			}
			printf ("%s  ", s_cmd->redirects[i]);
		}
			printf ("\n");
			i = 0;
			printf ("s_cmd[%d]->here_docs = ", x);
		if (s_cmd->here_docs != NULL)
		{
			while (s_cmd->here_docs[i] != NULL)
			{
				printf ("%s  ", s_cmd->here_docs[i]);
				i++;
			}
			printf ("%s  ", s_cmd->here_docs[i]);
		}
			printf ("\n");
		if (s_cmd->next != NULL)
			s_cmd = s_cmd->next;
		else
			stop = 1;
		x++;
	}
}

static int	count_tab(t_tkn *tkn, int end)
{
	tkn->words = 0;
	tkn->redirects = 0;
	tkn->here_docs = 0;
	tkn->pipes = 0;
	while (tkn->lexemas[end] != NULL)
	{
		if (ft_strncmp(tkn->lexemas[end], "PIPE", 4) == 0)
		{
			tkn->pipes++;
			end++;
			break ;
		}
		else if (ft_strncmp(tkn->lexemas[end], "WORD", 4) == 0
			|| ft_strncmp(tkn->lexemas[end], "ASSIGNMENT_WORD", 15) == 0)
		{
			tkn->words++;
			end++;
		}
		else if (ft_strncmp(tkn->lexemas[end], "LESS", 4) == 0
			|| ft_strncmp(tkn->lexemas[end], "GREAT", 5) == 0
			|| ft_strncmp(tkn->lexemas[end], "DGREAT", 6) == 0)
		{
			tkn->redirects = tkn->redirects + 2;
			end = end + 2;
		}	
		else if (ft_strncmp(tkn->lexemas[end], "DLESS", 5) == 0)
		{
			tkn->here_docs = tkn->here_docs + 2;
			end = end + 2;
		}
	}
	printf("words %d\n", tkn->words);
	printf("redirects %d\n", tkn->redirects);
	printf("here_docs %d\n", tkn->here_docs);
	printf ("PIPES %d\n", tkn->pipes);
	return (end);
}

void	create_cmd_tab(t_tkn *tkn, t_cmd **cmd_tab)
{
	int	start;
	int	end;

	end = 0;
	start = 0;
	*cmd_tab = NULL;
	while (tkn->lexemas[start] != NULL)
	{
		end = count_tab(tkn, end);
		create_node(tkn, cmd_tab, start, end);
		start = end;
	}
//	printf_cmd_tab(*cmd_tab);
	
}
