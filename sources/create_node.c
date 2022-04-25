#include "minishell.h"

static void	malloc_node_elements(t_tkn *tkn, t_cmd *s_cmd)
{
	s_cmd->pipes = tkn->pipes;
	s_cmd->next = NULL;
	s_cmd->words = NULL;
	s_cmd->redirects = NULL;
	s_cmd->here_docs = NULL;
	if (tkn->words != 0)
		s_cmd->words = ft_calloc(tkn->words + 1, sizeof(char *));
	if (tkn->redirects != 0)
		s_cmd->redirects = ft_calloc(tkn->redirects + 1, sizeof(char *));
	if (tkn->here_docs != 0)
		s_cmd->here_docs = ft_calloc(tkn->here_docs + 1, sizeof(char *));
}

static void	fill_node_elements_cont(t_tkn *tkn, char **array, int start)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
			i++;
	}
	array[i] = ft_strdup(tkn->tokens[start]);
	i++;
	array[i] = NULL;

}

static int	fill_node_elements(t_tkn *tkn, t_cmd *s_cmd, int start)
{
	if (ft_strncmp(tkn->lexemas[start], "WORD", 4) == 0
		|| ft_strncmp(tkn->lexemas[start], "ASSIGNMENT_WORD", 15) == 0)
			fill_node_elements_cont(tkn, s_cmd->words, start);
	else if (ft_strncmp(tkn->lexemas[start], "DLESS", 4) == 0)
	{
		fill_node_elements_cont(tkn, s_cmd->here_docs, start);
		start++;
		fill_node_elements_cont(tkn, s_cmd->here_docs, start);
	}
	else if (ft_strncmp(tkn->lexemas[start], "LESS", 4) == 0
			|| ft_strncmp(tkn->lexemas[start], "GREAT", 5) == 0
			|| ft_strncmp(tkn->lexemas[start], "DGREAT", 6) == 0)
	{
		fill_node_elements_cont(tkn, s_cmd->redirects, start);
		start++;
		fill_node_elements_cont(tkn, s_cmd->redirects, start);
	}
	start++;
	return (start);
}

void	create_node(t_tkn *tkn, t_cmd **cmd_tab, int start, int end)
{
	t_cmd	*s_cmd;
	t_cmd	*last;

	printf("entrei\n");
	s_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!s_cmd)
		return ;
	malloc_node_elements(tkn, s_cmd);
	while (start < end)
		start = fill_node_elements(tkn, s_cmd, start);
	if (*cmd_tab == NULL)
	{
		*cmd_tab = s_cmd;
//		printf("cmd_tab words %s\n", cmd_tab->words[0]);
	}
	else
	{
//		printf("cmd_tab words %s\n", cmd_tab->words[0]);
		last = *cmd_tab;
		while (last->next != NULL)
			last = last->next;
		last->next = s_cmd;
	}
}

