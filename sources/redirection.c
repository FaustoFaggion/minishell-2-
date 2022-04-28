#include "minishell.h"

//void	redirection(t_cmd **cmd_tab)
void	redirection(t_cmd **cmd)
{
	int	i;
//	t_cmd *s_cmd;

//	s_cmd = *cmd_tab;
//	while(s_cmd != NULL)
//	{
		i = 0;
		if ((*cmd)->redirects != NULL)
		{
			while ((*cmd)->redirects[i] != NULL)
			{
				printf("i %d redirects %s\n", i, (*cmd)->redirects[i]);
				if (ft_strncmp((*cmd)->redirects[i], "DGREAT", 6) == 0)
				{
					if((*cmd)->fd_out != -1)
						close((*cmd)->fd_out);
					i++;
					(*cmd)->fd_out = open((*cmd)->redirects[i], O_RDWR | O_APPEND
						| O_CREAT, 0777);
				}
				else if (ft_strncmp((*cmd)->redirects[i], "GREAT", 5) == 0)
				{
					if((*cmd)->fd_out != -1)
						close((*cmd)->fd_out);
					i++;
					(*cmd)->fd_out = open((*cmd)->redirects[i], O_RDWR | O_TRUNC
						| O_CREAT, 0777);
				}
				else if (ft_strncmp((*cmd)->redirects[i], "LESS", 4) == 0)
				{
					if((*cmd)->fd_in != -1)
						close((*cmd)->fd_in);
					i++;
					(*cmd)->fd_in = open((*cmd)->redirects[i], O_RDONLY);
				}
				i++;
			}
		}
//		s_cmd = s_cmd->next;
//	}	
}
