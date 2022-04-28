#include "minishell.h"

static int	exec_child(t_tkn *tkn, t_cmd **s_cmd, int **pipes, int i)
{
	int	x;
	
//	handle_signal_child();
	if ((*s_cmd)->next != NULL)
	{
		if ((*s_cmd)->redirects == NULL)
			dup2(pipes[i][1], STDOUT_FILENO);
		else
		{
			dup2((*s_cmd)->fd_out, STDOUT_FILENO);
			if ((*s_cmd)->fd_in != -1)
				dup2((*s_cmd)->fd_in, STDIN_FILENO);
		}
	}
	x = 0;
	while (x < tkn->pid)
	{
		close(pipes[x][0]);
		close(pipes[x][1]);
		x++;
	}
	pipes[i] = NULL;
	if ((*s_cmd)->fd_in != -1)
		close((*s_cmd)->fd_in);
	if ((*s_cmd)->fd_out != -1)
		close((*s_cmd)->fd_out);
//	if (built_in_cmd(tkn, i) == 1)
//	{
	if (execve((*s_cmd)->path, (*s_cmd)->words, tkn->envp) == -1)
	{
		write(2, "error execve\n", 13);
		exit(1);
	}
	//	exit_shell(tkn);
//	}
	//exit_shell(tkn);
	free_tab(&tkn->envp, tkn->envp_count);
	rl_clear_history();
	exit(0);
	return (0);
}

int	path_setup(t_cmd **s_cmd, t_tkn *tkn)
{
	int		x;
	char	*temp;

	x = 0;
	if (tkn->path != NULL)
	{
		while (tkn->path[x] != NULL)
		{
			(*s_cmd)->path = ft_strjoin(tkn->path[x], "/");
			if ((*s_cmd)->path == NULL)
				exit(1);
			temp = (*s_cmd)->path;
			(*s_cmd)->path = ft_strjoin(temp, (*s_cmd)->words[0]);
			free(temp);
			if ((*s_cmd)->path == NULL)
				exit(1);
			if (access((*s_cmd)->path, F_OK) == 0)
				return (0);
			free((*s_cmd)->path);
			(*s_cmd)->path = NULL;
			x++;
		}
	}
	setup_error((*s_cmd)->words[0], 0);
	return (1);
}
static void	s_cmd_setup(t_cmd **s_cmd, t_tkn *tkn)
{
	if (ft_strchr((*s_cmd)->words[0], '/') == NULL)
	{
		//if (built in)
		path_setup(s_cmd, tkn);
	}
}
static void	create_pipes(int ***pipes, t_tkn *tkn)
{
	int	fd[2];
	int	i;

	*pipes = (int **)calloc((tkn->pid * 2) + 1, sizeof(int *));
	i = 0;
	while (i < tkn->pid)
	{
		if(pipe(fd) == -1)
			exit(write(1, "pipe error\n", 11));
		(*pipes)[i] = (int *)calloc(2, sizeof(int));
		(*pipes)[i][0] = fd[0];
		(*pipes)[i][1] = fd[1];
		i++;
	}
	(*pipes)[i] = NULL;

}

void	exec_cmd_tab(t_cmd **cmd_tab, t_tkn *tkn)
{
	t_cmd	*s_cmd;
	int		**pipes;
	int		i;
	int		temp_in;
	int		temp_out;

	temp_in = dup(STDIN_FILENO);
	temp_out = dup(STDOUT_FILENO);
	s_cmd = *cmd_tab;
	create_pipes(&pipes, tkn);
	i = 0;
	printf("fd[0] %d, fd[1] %d\n", pipes[0][0], pipes[0][1]);
	while(s_cmd != NULL)
	{
		s_cmd_setup(&s_cmd, tkn);	
		s_cmd->pid = fork();
		i++;
		if (s_cmd->pid < 0)
			exit(write(1, "fork error\n", 11));
		if (s_cmd->pid == 0)
			exec_child(tkn, &s_cmd, pipes, i);
		if (s_cmd->next != NULL)
			dup2(pipes[i][0], STDIN_FILENO);
//		close(pipes[i][0]);
//		close(pipes[i][1]);
		s_cmd = s_cmd->next;
	}
	while (i > 0)
	{
		waitpid(-1, NULL, 0);
		i--;
	}
	//dup2(fd[0], STDOUT_FILENO);
}