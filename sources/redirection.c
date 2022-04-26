#include "minishell.h"

void	redirection(t_cmd **cmd_tab)
{
	int	i;
	t_cmd *s_cmd;

	s_cmd = *cmd_tab;
	while(s_cmd != NULL)
	{
		i = 0;
		if (s_cmd->redirects != NULL)
		{
			while (s_cmd->redirects[i] != NULL)
			{
				printf("i %d redirects %s\n", i, s_cmd->redirects[i]);
				if (ft_strncmp(s_cmd->redirects[i], "DGREAT", 6) == 0)
				{
					if(s_cmd->fd_out != 1)
						close(s_cmd->fd_out);
					i++;
					s_cmd->fd_out = open(s_cmd->redirects[i], O_RDWR | O_APPEND
						| O_CREAT, 0777);
				}
				else if (ft_strncmp(s_cmd->redirects[i], "GREAT", 5) == 0)
				{
					if(s_cmd->fd_out != 1)
						close(s_cmd->fd_out);
					i++;
					s_cmd->fd_out = open(s_cmd->redirects[i], O_RDWR | O_TRUNC
						| O_CREAT, 0777);
				}
				else if (ft_strncmp(s_cmd->redirects[i], "LESS", 4) == 0)
				{
					if(s_cmd->fd_in != 0)
						close(s_cmd->fd_in);
					i++;
					s_cmd->fd_in = open(s_cmd->redirects[i], O_RDONLY);
				}
				i++;
			}
		}
		s_cmd = s_cmd->next;
	}	
}
