#include "minishell.h"

static char	*prompt_line(void)
{
	char	dir[1024];
	char	*user;
	char	*temp;
	char	*swap;

	user = getenv("USER");
	getcwd(dir, sizeof(dir));
	temp = ft_strjoin(user, dir);
	swap = temp;
	temp = ft_strjoin(swap, "$");
	free(swap);
	swap = temp;
	temp = ft_strjoin(swap, " ");
	free(swap);
	return (temp);
}

static int	check_double_quote(t_tkn *tkn)
{
	char	*temp;
	int		is_clear;

	temp = ft_strtrim(tkn->line, " ");
	is_clear = 0;
	if (!temp || ft_strlen(temp) == 0)
		is_clear = 1;
	free(temp);
	return (is_clear);
}

int		get_prompt(t_tkn *tkn)
{
	char	*line;
	int		ret;

	line = prompt_line();
	tkn->line = readline(line);
	free(line);
	if (!tkn->line)
	{
		exit_shell(tkn);
		free_tab(&tkn->envp, tkn->envp_count);
		rl_clear_history();
		exit(0);
	}
	ret = check_double_quote(tkn);
	add_history(tkn->line);
	return(ret);
}