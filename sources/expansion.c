/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/18 14:52:42 by fagiusep         ###   ########.fr       */
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

static int	join_tkn_sp_char(char **quote, char **temp, char **exp_envp, char **temp_2)
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

static void	expand_special_char(char **exp_envp)
{
	char	*user;
	char	*temp;
	char	*swap;
	
	if (ft_strncmp(*exp_envp, "~", 1) == 0)
	{
		user = getenv("USER");
		temp = ft_strjoin("/home/", user);
		swap = 	*exp_envp;
		*exp_envp = temp;
		free(swap);
	}
}

static int	prepare_special_char(t_tkn **tkn, char **quote, int j)
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
	expand_special_char(&exp_envp);
	j = join_tkn_sp_char(quote, &temp, &exp_envp, &temp_2);
	return (j - 1);
}

static int	special_char(t_tkn **tkn, char **token, int j)
{
	if (j == 0)
	{
		if ((*token)[j] == '~' && ((*token)[j + 1] == '\0'
				|| (*token)[j + 1] == '/'))
			j = prepare_special_char(tkn, token, j);
	}
	else
	{
		if ((*token)[j] == '~' && (*token)[j - 1] == ' '
				&& ((*token)[j + 1] == '\0' || (*token)[j + 1] == '/'))
			j = prepare_special_char(tkn, token, j);
	}
	return (j);
}

void	expansion(t_tkn *tkn)
{
	int		i;
	int		j;

	i = 0;
	while (tkn->tokens[i])
	{
		j = 0;
		while (tkn->tokens[i][j] != '\0')
		{
			if(j == 0)
				exec_cmd_path_ck(tkn, i);
			if (tkn->tokens[i][j] == '~')
				j = special_char(&tkn, &tkn->tokens[i], j);
			if (tkn->tokens[i][j] == '$')
				j = prepare_envp(&tkn, &tkn->tokens[i], j);
			else if (tkn->tokens[i][j] == '\"')
				j = prepare_quote(&tkn, &tkn->tokens[i], j, i);
			else if (tkn->tokens[i][j] == '\'')
				j = s_quoted(&tkn->tokens[i], j);
			j++;
		}
		i++;
	}
}
