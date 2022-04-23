#include "minishell.h"

static void	malloc_node_elements(t_tkn *tkn, t_cmd *s_cmd)
{
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
	array[i] = tkn->tokens[start];
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

void	create_node(t_tkn *tkn, int start, int end)
{
	t_cmd	*s_cmd;
	int		i;

	s_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!s_cmd)
		return ;
	malloc_node_elements(tkn, s_cmd);
	while (start < end)
		start = fill_node_elements(tkn, s_cmd, start);


	i = 0;
	printf ("WORDS = ");
	if (s_cmd->words != NULL)
	{
		while (s_cmd->words != NULL && s_cmd->words[i] != NULL)
		{
			printf ("%s  ", s_cmd->words[i]);
			i++;
		}
		printf ("%s \n", s_cmd->words[i]);
	}
	i = 0;
	printf ("REDIRECTS = ");
	if (s_cmd->redirects != NULL)
	{
		while (s_cmd->redirects[i] != NULL)
		{
			printf ("%s  ", s_cmd->redirects[i]);
			i++;
		}
		printf ("%s\n", s_cmd->redirects[i]);
	}
	printf ("\n");
	i = 0;
	printf ("HERE_DOCS = ");
	if (s_cmd->here_docs != NULL)
	{
		while (s_cmd->here_docs != NULL && s_cmd->here_docs[i] != NULL)
		{
			printf ("%s  ", s_cmd->here_docs[i]);
			i++;
		}
		printf ("%s\n", s_cmd->here_docs[i]);
	}
	printf ("\n");
}

