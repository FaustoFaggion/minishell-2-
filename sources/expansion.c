/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/25 19:48:08 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
*/
static int	join_tilde_expansion(char **quote, char **temp, char **exp_envp, char **temp_2)
{
	char	*swap;
	int		j;
	
	swap = *temp;
	*temp = ft_strjoin(swap, *exp_envp);
	free(swap);
	j = ft_strlen(*temp);
	swap = *temp;
	*temp = ft_strjoin(swap, *temp_2);
	free(swap);
	swap = *quote;
	*quote = ft_strdup(*temp);
	free(*temp);
	free(swap);
	free(*exp_envp);
	free(*temp_2);
	return (j);
}

static int	check_expansion(char **quote, int j)
{
	if ((*quote)[j] == '~')
		j++;
	return (j);
}

static void	expand_tilde(t_tkn **tkn, char **exp_envp, char *temp_2)
{
	char	*user;
	char	*temp;
	char	*swap;
	if (ft_strncmp(temp_2, (*tkn)->logname, ft_strlen((*tkn)->logname)) != 0)
	{
		if (ft_strncmp(*exp_envp, "~", 1) == 0)
		{
			user = getenv("LOGNAME");
			temp = ft_strjoin("/home/", user);
			swap = 	*exp_envp;
			*exp_envp = temp;
			free(swap);
		}
	}
	else
	{
		printf("entrei\n");
		swap = 	*exp_envp;
		*exp_envp = ft_strdup("/home/");
		free(swap);
	}
}

static int	prepare_tilde(t_tkn **tkn, char **quote, int j)
{
	char	*temp;
	char	*temp_2;
	char	*exp_envp;

	temp = ft_substr(*quote, 0, j);
	(*tkn)->exp_start = j;
	j = check_expansion(quote, j);
	exp_envp = ft_substr(*quote, (*tkn)->exp_start, j - (*tkn)->exp_start);
	(*tkn)->exp_start = j;
	while ((*quote)[j] != '\0')
		j++;
	temp_2 = ft_substr(*quote, (*tkn)->exp_start, j - (*tkn)->exp_start);
	expand_tilde(tkn, &exp_envp, temp_2);
	j = join_tilde_expansion(quote, &temp, &exp_envp, &temp_2);
	return (j - 1);
}

static int	tilde_expansion(t_tkn *tkn, char **token, int j)
{
	char	*temp;
	
	temp = ft_substr(*token, 1, ft_strlen(*token) - 1);
	
	if ((*token)[j + 1] == '\0' || (*token)[j + 1] == '/')
		j = prepare_tilde(&tkn, token, j);
	else
	{
		printf("logname: %s\n", tkn->logname);
		if (ft_strncmp(tkn->logname, temp, ft_strlen(tkn->logname)) == 0)
		{
			j = prepare_tilde(&tkn, token, j);
		}
	}
	free(temp);
	return (j);
}

void	expansion(t_tkn *tkn, t_cmd **cmd_tab)
{
	int		i;
	int		j;
	int		flag;
	t_cmd	*cmd;
	
	flag = 0;
	cmd = *cmd_tab;
	while (flag == 0)
	{
		i = 0;
		while (cmd->words[i] != NULL)
		{
			j = 0;
			while (cmd->words[i][j] != '\0')
			{
//					exec_cmd_path_ck(tkn, i);
				if(j == 0)
				{
					if (cmd->words[i][j] == '~')
						j = tilde_expansion(tkn, &cmd->words[i], j);
				}
/*				if (tkn->tokens[i][j] == '$')
					j = prepare_envp(&tkn, &tkn->tokens[i], j);
				else if (tkn->tokens[i][j] == '\"')
					j = prepare_quote(&tkn, &tkn->tokens[i], j, i);
				else if (tkn->tokens[i][j] == '\'')
					j = s_quoted(&tkn->tokens[i], j);
*/				j++;
			}
			i++;
		}
	if (cmd->next == NULL)
		flag = 1;
	else
		cmd = cmd->next;
	}
}
