#include "minishell.h"

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
	char	*log;
	int		index;

	log = getenv("LOGNAME");
	index = ft_strlen(log);
	if ((*quote)[j] == '~')
		j++;
	if ((*quote)[j] != '/' && (*quote)[j] != '\0')
		j+= index;
	return (j);
}

static void	expand_tilde(char **exp_envp)
{
	char	*temp;
	char	*swap;
			
	temp = ft_strdup(getenv("HOME"));
	swap = 	*exp_envp;
	*exp_envp = temp;
	free(swap);
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
	expand_tilde(&exp_envp);
	j = join_tilde_expansion(quote, &temp, &exp_envp, &temp_2);
	return (j - 1);
}

int	expansion_tilde(t_tkn *tkn, char **token, int j)
{
	char	*temp;
	
	temp = ft_substr(*token, 1, ft_strlen(*token) - 1);
	
	if ((*token)[j + 1] == '\0' || (*token)[j + 1] == '/')
		j = prepare_tilde(&tkn, token, j);
	else
	{
		if (ft_strncmp(tkn->logname, temp, ft_strlen(tkn->logname)) == 0)
		{
			if (temp[ft_strlen(tkn->logname + 1) + 1] == '/'
				|| temp[ft_strlen(tkn->logname + 1) + 1] == '\0')
				j = prepare_tilde(&tkn, token, j);
		}
	}
	free(temp);
	return (j);
}
