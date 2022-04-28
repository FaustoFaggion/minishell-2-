#include "minishell.h"

static void	malloc_node_elements(t_tkn *tkn, t_cmd *s_cmd)
{
	s_cmd->fd_in = -1;
	s_cmd->fd_out = -1;
	s_cmd->pipes = tkn->end_cmd_pipe;
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

static void	fill_node_elements_cont(t_tkn *tkn, char **array, int start, int k)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
			i++;
	}
	if (k == 0)
		array[i] = ft_strdup(tkn->tokens[start]);
	else if (k == 1)
		array[i] = ft_strdup(tkn->lexemas[start]);
	i++;
	array[i] = NULL;

}

static int	fill_node_elements(t_tkn *tkn, t_cmd *s_cmd, int start)
{
	if (ft_strncmp(tkn->lexemas[start], "WORD", 4) == 0
		|| ft_strncmp(tkn->lexemas[start], "ASSIGNMENT_WORD", 15) == 0)
			fill_node_elements_cont(tkn, s_cmd->words, start, 0);
	else if (ft_strncmp(tkn->lexemas[start], "DLESS", 4) == 0)
	{
		fill_node_elements_cont(tkn, s_cmd->here_docs, start, 1);
		start++;
		fill_node_elements_cont(tkn, s_cmd->here_docs, start, 0);
	}
	else if (ft_strncmp(tkn->lexemas[start], "LESS", 4) == 0
			|| ft_strncmp(tkn->lexemas[start], "GREAT", 5) == 0
			|| ft_strncmp(tkn->lexemas[start], "DGREAT", 6) == 0)
	{
		fill_node_elements_cont(tkn, s_cmd->redirects, start, 1);
		start++;
		fill_node_elements_cont(tkn, s_cmd->redirects, start, 0);
	}
	start++;
	return (start);
}

static void is_exec_fork(t_cmd *s_cmd, t_tkn *tkn)
{
	if (s_cmd->words != NULL)
	{
		if (ft_strncmp(s_cmd->words[0], "cd\0", 3) != 0)
			tkn->pid++;
	}
}
void	create_node(t_tkn *tkn, t_cmd **cmd_tab, int start, int end)
{
	t_cmd	*s_cmd;
	t_cmd	*last;

	s_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!s_cmd)
		return ;
	malloc_node_elements(tkn, s_cmd);
	while (start < end)
		start = fill_node_elements(tkn, s_cmd, start);
	if (*cmd_tab == NULL)
		*cmd_tab = s_cmd;
	else
	{
		last = *cmd_tab;
		while (last->next != NULL)
			last = last->next;
		last->next = s_cmd;
	}
	is_exec_fork(s_cmd, tkn);
	printf ("PID %d\n", tkn->pid);
	printf ("PIPE %d\n", tkn->pipe);
}

