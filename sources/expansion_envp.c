/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:34:01 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/18 14:53:17 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_expansion_2(char **tkn, int j)
{
	if ((*tkn)[j] == 95)
		return (0);
	else if ((*tkn)[j] >= 48 && (*tkn)[j] <= 57)
		return (0);
	else if ((*tkn)[j] >= 65 && (*tkn)[j] <= 90)
		return (0);
	else if ((*tkn)[j] >= 97 && (*tkn)[j] <= 122)
		return (0);
	return (1);
}

static int	check_expansion_1(char **tkn, int j)
{
	if ((*tkn)[j] == 33 || (*tkn)[j] == 96 || (*tkn)[j] == 35)
		return (0);
	else if ((*tkn)[j] >= 37 && (*tkn)[j] <= 60)
		return (0);
	else if ((*tkn)[j] == 62 || (*tkn)[j] == 64)
		return (0);
	else if ((*tkn)[j] >= 91 && (*tkn)[j] <= 94)
		return (0);
	else if ((*tkn)[j] >= 123 && (*tkn)[j] <= 126)
		return (0);
	return (1);
}

static int	check_expansion(t_tkn **tkn, char **quote, int j)
{
	if ((*quote)[j] == '?')
	{
		j++;
		printf("<%d>\n", global_exit);
		(*tkn)->exp_flag = 0;
	}	
	else if (check_expansion_1(quote, j) == 0)
	{
		(*tkn)->exp_start--;
		while ((*quote)[j] != ' ' && (*quote)[j] != '\0'
			&& check_expansion_1(quote, j) == 0)
			j++;
		(*tkn)->exp_flag = 1;
	}
	else
	{
		while ((*quote)[j] != ' ' && (*quote)[j] != '\0'
			&& check_expansion_2(quote, j) == 0)
			j++;
		(*tkn)->exp_flag = 0;
	}
	return (j);
}

static void	expand_envp(t_tkn **tkn, char **exp_envp)
{
	char	**temp;
	char	*swap;
	int		j;

	j = 0;
	while ((*tkn)->envp[j] != NULL)
	{
		if (ft_strncmp((*tkn)->envp[j], *exp_envp, ft_strlen(*exp_envp)) == 0)
		{
			temp = ft_split((*tkn)->envp[j], '=');
			swap = *exp_envp;
			*exp_envp = ft_strdup(temp[1]);
			free_tab(&temp, 2);
			free(swap);
			break ;
		}
		j++;
	}
	if ((*tkn)->envp[j] == NULL)
	{
		swap = *exp_envp;
		*exp_envp = ft_strdup(" ");
		free(swap);
	}
}

int	prepare_envp(t_tkn **tkn, char **quote, int j) 
{
	char	*temp;
	char	*temp_2;
	char	*exp_envp;
	char	*swap;

	if ((*quote)[j + 1] == '\0')
		return (j);
	temp = ft_substr(*quote, 0, j);
	j++;
	(*tkn)->exp_start = j;
	j = check_expansion(tkn, quote, j);
	exp_envp = ft_substr(*quote, (*tkn)->exp_start, j - (*tkn)->exp_start);
	swap = exp_envp;
	exp_envp = ft_strjoin(swap, "=");
	free(swap);
	(*tkn)->exp_start = j;
	while ((*quote)[j] != '\0')
		j++;
	temp_2 = ft_substr(*quote, (*tkn)->exp_start, j - (*tkn)->exp_start);
	if ((*tkn)->exp_flag == 0)
		expand_envp(tkn, &exp_envp);
	j = join_token(quote, &temp, &exp_envp, &temp_2);
	return (j - 1);
}
