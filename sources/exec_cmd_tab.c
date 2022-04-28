#include "minishell.h"

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
static int	s_cmd_setup(t_cmd **s_cmd, t_tkn *tkn)
{
	int	ret;

	ret = 0;
	if (ft_strchr((*s_cmd)->words[0], '/') == NULL)
	{
		//if (built in)
		ret = path_setup(s_cmd, tkn);
		printf("s_cmd->path %s\n", (*s_cmd)->path);
	}
	return (ret);
}

static void	redirect_std_fileno(t_cmd **s_cmd, int fd[])
{
	char	*temp;
	int		flag;
	int		i;

	close(fd[0]);
//	(*s_cmd)->fd_out = -1;
//	(*s_cmd)->fd_in = -1;
	flag = 0;
	i = 0;
	while ((*s_cmd)->redirects[i] != NULL)
	{
		if (ft_strncmp((*s_cmd)->redirects[i], "DGREAT", 6) == 0)
		{
			if((*s_cmd)->fd_out != -1)
				close((*s_cmd)->fd_out);
			i++;
			(*s_cmd)->fd_out = open((*s_cmd)->redirects[i], O_RDWR | O_APPEND
					| O_CREAT, 0777);
			flag = 1;
		}
		else if (ft_strncmp((*s_cmd)->redirects[i], "GREAT", 5) == 0)
		{
			if ((*s_cmd)->fd_out != -1)
				close((*s_cmd)->fd_out);
			i++;
			(*s_cmd)->fd_out = open((*s_cmd)->redirects[i], O_RDWR | O_TRUNC
					| O_CREAT, 0777);
			flag = 1;
		}
		else if (ft_strncmp((*s_cmd)->redirects[i], "LESS", 4) == 0)
		{
			if((*s_cmd)->fd_in != -1)
				close((*s_cmd)->fd_in);
			i++;
			(*s_cmd)->fd_in = open((*s_cmd)->redirects[i], O_RDONLY);
			dup2((*s_cmd)->fd_in, STDIN_FILENO);			
		}
		else
			break;
		i++;
	}
	if (flag == 1)
	{
		temp = ft_get_next_line((*s_cmd)->fd_out);
		if ((*s_cmd)->fd_out < 0)
		{
			printf("bash: s: Arquivo ou diretório inexistente\n");
			return ;
		} 
		else
			dup2((*s_cmd)->fd_out, STDOUT_FILENO);
	}
}

static void	define_std_fileno(int fd[], t_cmd **s_cmd)
{
		if ((*s_cmd)->redirects == NULL)
		{
			if ((*s_cmd)->next != NULL)
				dup2(fd[1], STDOUT_FILENO);
		}
		else
		{
			redirect_std_fileno(s_cmd, fd);
			if ((*s_cmd)->fd_out == -1)
				dup2(fd[1], STDOUT_FILENO);

		}
}

static int	exec_child(t_tkn *tkn, int fd[], t_cmd **s_cmd)
{
//	handle_signal_child();
	close(fd[0]);
	define_std_fileno(fd, s_cmd);
	close(fd[1]);
//	if (built_in_cmd(tkn, i) == 1)
//	{
		if (execve((*s_cmd)->path, (*s_cmd)->words, tkn->envp) == -1)
		{
			write(2, "error execve\n", 13);
			exit(1);
		}
//		exit_shell(tkn);
//	}
//	exit_shell(tkn);
	free_tab(&tkn->envp, tkn->envp_count);
	rl_clear_history();
	exit(0);
	return (0);
}

static void	exec_cmd(t_cmd **s_cmd, t_tkn *tkn)
{
	int	fd[2];
	int	pid;
	int	wstatus;

//	if (check_built_in(tkn) == 1)
//	{
		if (pipe(fd) == -1)
			exit(write(1, "pipe error\n", 11));
		if (s_cmd_setup(s_cmd, tkn) == 0)
		{
			pid = fork();
			if (pid < 0)
				exit(write(1, "fork error\n", 11));
			if (pid == 0)
				exec_child(tkn, fd, s_cmd);
			waitpid(pid, &wstatus, 0);
			if (!WIFSIGNALED(wstatus))
				global_exit = WEXITSTATUS(wstatus);
		}
//		handle_signal_parent();
		close(fd[1]);
		if ((*s_cmd)->next != NULL)
		{
			dup2(fd[0], STDIN_FILENO);
		}
		close(fd[0]);
//	}
}

void	exec_cmd_tab(t_cmd **cmd_tab, t_tkn *tkn)
{
	t_cmd	*s_cmd;
	int		temp_in;
//	int		temp_out;

	temp_in = dup(STDIN_FILENO);
//	temp_out = dup(STDOUT_FILENO);
	s_cmd = *cmd_tab;
	while (s_cmd != NULL)
	{
		exec_cmd(&s_cmd, tkn);
		s_cmd = s_cmd->next;
	}
	dup2(temp_in, STDIN_FILENO);
}