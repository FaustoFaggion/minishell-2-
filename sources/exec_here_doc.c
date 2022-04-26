/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:24:54 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/26 15:45:37 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	exec_cmd_less(t_tkn *tkn, int i)
{
	if(tkn->fd_in != 0)
		close(tkn->fd_in);
	tkn->fd_in = open(tkn->cmd[i][1], O_RDONLY);
	if (tkn->fd_in < 0)
	{
		setup_error(tkn->cmd[i][1], 1);
		return ;
	}
	else
		dup2(tkn->fd_in, STDIN_FILENO);
}
*/
static void	wr_line(char *limiter, int len, int fd[])
{
	char	*line;

	close(fd[0]);
//	handle_signal_child();
	while (1)
	{
		write(1, "> ", 2);
		line = ft_get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			write(2, "aviso de erro here_doc", 22);
			break ;
		}
		if (ft_strncmp(limiter, line, len) == 0)
		{
			if (line[len] == '\n')
			{
				free(line);
				ft_get_next_line(-1);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
		}
		else
		{
			write(fd[1], line, ft_strlen(line));
		}
		free(line);
	}
	close(fd[1]);
	exit(0);
}

static int	exec_cmd(char *limiter)
{
	int	fd[2];
	int	len;
	int	pid;
	int	wstatus;
	
	if (pipe(fd) == -1)
		exit(write(1, "pipe error\n", 11));
	len = ft_strlen(limiter);
	pid = fork();
	if (pid < 0)
		exit(write(1, "fork error\n", 11));
	if (pid == 0)
		wr_line(limiter, len, fd);
	waitpid(pid, &wstatus, 0);
	if (!WIFSIGNALED(wstatus))
		global_exit = WEXITSTATUS(wstatus);
//	handle_signal_parent();
	close(fd[1]);
	return (fd[0]);
}

void	exec_here_doc(t_cmd **cmd_tab)
{
	t_cmd	*s_cmd;
	int		i;
	int 	fd;
	
	s_cmd = *cmd_tab;
	while (s_cmd != NULL)
	{
		if (s_cmd->here_docs != NULL)
		{
			i = 0;
			while (s_cmd->here_docs[i] != NULL)
			{
				i++;
				fd = exec_cmd(s_cmd->here_docs[i]);
				i++;
			}
		}
		s_cmd = s_cmd->next;
		if (s_cmd == NULL)
			dup2(fd, STDIN_FILENO);
		close(fd);
	}
}
