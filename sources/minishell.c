/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:20:20 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/23 08:17:56 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_recog(t_tkn *tkn)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	printf ("TOKENS = ");
	while (tkn->lexemas[i] != NULL)
	{
		printf ("%s  ", tkn->tokens[i]);
		i++;
	}
	printf ("%s  ", tkn->tokens[i]);
	printf ("\n");
	i = 0;
	printf ("LEXEMAS = ");
	while (tkn->lexemas[i] != NULL)
	{
		printf ("%s  ", tkn->lexemas[i]);
		i++;
	}
	printf ("%s  ", tkn->lexemas[i]);
	printf ("\n");
	x = 0;
	y = 0;
}

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

static void	init_tkn(t_tkn *tkn)
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

static void	envp_list_dup(t_tkn *tkn, char *envp[])
{
	int	x;

	x = 0;
	while (envp[x] != NULL)
		x++;
	tkn->envp_count = x;
	tkn->envp = (char **)malloc((x + 1) * sizeof(char *));
	x = 0;
	while (envp[x])
	{
		tkn->envp[x] = ft_strdup(envp[x]);
		x++;
	}
	tkn->envp[x] = NULL;
}

int	global_exit;

int	main(int argc, char *argv[], char *envp[])
{
	t_tkn	tkn;
	
	if (argc > 1)
	{
		printf("%s :Invalid number of arguments\n", argv[0]);
		global_exit = 1;
		return (1);
	}
	envp_list_dup(&tkn, envp);
	tkn.amb_v = NULL;
	while (1)
	{
//		handle_signal_prompt();
		init_tkn(&tkn);
		if (get_prompt(&tkn) == 0)
		{
			if (token_analysis(&tkn) == 0)
			{
				lexical_analysis(&tkn);
				if (sintax_analysis(&tkn) == 0)
				{
					//expansion(&tkn);
					cmd_tab(&tkn);
					//exec_cmd_tab(&tkn);
					if (DEBUG == 1)
						token_recog(&tkn);
				//	exit_shell(&tkn);
				}
			}
		}
		else
		//	exit_shell(&tkn);
			exit(0);
		exit(0);
	}
}