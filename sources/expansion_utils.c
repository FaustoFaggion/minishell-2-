/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:12:38 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/26 17:12:39 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_token(char **quote, char **temp, char **exp_envp, char **temp_2)
{
	char	*swap;
	int		j;

	if ((*exp_envp)[0] != ' ')
	{
		swap = *temp;
		*temp = ft_strjoin(swap, *exp_envp);
		j = ft_strlen(*temp);
		free(swap);
	}
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
