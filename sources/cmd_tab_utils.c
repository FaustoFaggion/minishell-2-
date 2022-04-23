#include "minishell.h"

static int	count_word(t_tkn *tkn, int i)
{
	int	count;

	count = 0;
	while (ft_strncmp(tkn->lexemas[i + count], "WORD", 4) == 0
		|| ft_strncmp(tkn->lexemas[i + count], "ASSIGNMENT_WORD", 15) == 0)
	{
		count++;
		if (tkn->lexemas[i + count] == NULL)
			break ;
	}
	return (count);
}

static void	utils_word(t_tkn *tkn, char ***temp, char ***temp_lex)
{
	tkn->cmd[tkn->cmd_count] = *temp;
	tkn->cmd_lex[tkn->cmd_count] = *temp_lex;
	tkn->cmd_count++;
}

int	cmd_word(t_tkn *tkn, int i)
{
	int		count;
	int		j;
	char	**temp;
	char	**temp_lex;

	count = count_word(tkn, i);
	temp = (char **) malloc(sizeof(char *) * (count + 1));
	if (temp == NULL)
		return (1);
	temp_lex = (char **) malloc(sizeof(char *) * (count + 1));
	if (temp_lex == NULL)
		return (1);
	j = 0;
	while (count > 0)
	{
		temp[j] = ft_strdup(tkn->tokens[i]);
		temp_lex[j] = ft_strdup(tkn->lexemas[i]);
		j++;
		i++;
		count--;
	}
	temp[j] = NULL;
	temp_lex[j] = NULL;
	utils_word(tkn, &temp, &temp_lex);
	return (i);
}
