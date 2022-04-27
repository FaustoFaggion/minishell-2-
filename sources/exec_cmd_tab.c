#include "minishell.h"

static int	exec_child(t_tkn *tkn, t_cmd **s_cmd, int fd[])
{
	
//	handle_signal_child();
	close(fd[0]);
	close(fd[1]);
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

void	exec_cmd_tab(t_cmd **cmd_tab, t_tkn *tkn)
{
	t_cmd	*s_cmd;
	int		fd[2];
	int		i;

	s_cmd = *cmd_tab;
	i = 0;
	while(s_cmd != NULL)
	{
//		if (s_cmd->pipes == 1) verificar builtins que não executam fork
//		{
			s_cmd_setup(&s_cmd, tkn);
			if(pipe(fd) == -1)
				exit(write(1, "pipe error\n", 11));
			
			if (s_cmd->pipes == 1)
			{
				if (s_cmd->redirects == NULL)
					s_cmd->fd_out = fd[0];
			}
			if (s_cmd->next != NULL)
				s_cmd->next->fd_in = fd[1];
			dup2(s_cmd->fd_in, STDIN_FILENO);
			dup2(s_cmd->fd_out, STDOUT_FILENO);
			s_cmd->pid = fork();
			i++;
			if (s_cmd->pid < 0)
				exit(write(1, "fork error\n", 11));
			if (s_cmd->pid == 0)
			exec_child(tkn, &s_cmd, fd);
//		}
		s_cmd = s_cmd->next;
	}
	while (i > 0)
	{
		waitpid(-1, NULL, 0);
		i--;
	}
	close(fd[1]);
	close(fd[0]);
	//dup2(fd[0], STDOUT_FILENO);
}