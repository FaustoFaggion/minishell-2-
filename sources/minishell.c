/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:20:20 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/27 19:46:49 by fagiusep         ###   ########.fr       */
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
	
	i = 0;
	while (tkn->envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", tkn->envp[i], 5) == 0)
		{
			temp = ft_split(tkn->envp[i], '=');
			tkn->path = ft_split(temp[1], ':');
			if (tkn->path == NULL)
			{
				write(2, "copy_path error\n", 33);
				return ;
			}
			free_tab(&temp, 2);
		}
	//	printf("%s\n", tkn->envp[i]);
		i++;
	}
}

static void	init_tkn(t_tkn *tkn)
{
	tkn->line = NULL;
	tkn->tokens = NULL;
	tkn->lexemas = NULL;
	tkn->path = NULL;
	tkn->pid = 0;
	tkn->pipe = 0;
	copy_path(tkn);
	tkn->path_count = 0;
	tkn->pid = 0;
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
	t_cmd	*cmd_tab;
	
	if (argc > 1)
	{
		printf("%s :Invalid number of arguments\n", argv[0]);
		global_exit = 1;
		return (1);
	}
	cmd_tab = NULL;
	envp_list_dup(&tkn, envp);
	while (1)
	{
//		handle_signal_prompt();
		init_tkn(&tkn);
		if (get_prompt(&tkn, &cmd_tab) == 0)
		{
			if (token_analysis(&tkn) == 0)
			{
				lexical_analysis(&tkn);
				if (sintax_analysis(&tkn) == 0)
				{
					create_cmd_tab(&tkn, &cmd_tab);
					expansion(&tkn, &cmd_tab);
				//	redirection(&cmd_tab);
					exec_here_doc(&cmd_tab);
					exec_cmd_tab(&cmd_tab, &tkn);
					printf_cmd_tab(&cmd_tab);
					if (DEBUG == 1)
						token_recog(&tkn);
					exit_shell(&tkn, &cmd_tab);
				}
				else
					exit_shell(&tkn, &cmd_tab);
			}
		}
		else
			exit_shell(&tkn, &cmd_tab);
	//	exit(0);
	}
}