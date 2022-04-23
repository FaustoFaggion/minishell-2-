/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:51:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/23 10:53:48 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	return (end);
}

void	cmd_tab(t_tkn *tkn)
{
	int	start;
	int	end;

	end = 0;
	start = 0;
	while (tkn->lexemas[start] != NULL)
	{
		end = count_tab(tkn, end);
		create_node(tkn, start, end);
		start = end;
	}
	
}
