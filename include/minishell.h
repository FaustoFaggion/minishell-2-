#ifndef MINISHELL_H
# define MINISHELL_H

#define _GNU_SOURCE
#define DEBUG 1
#define PIPE "PIPE"
#define LESS "LESS"
#define DLESS "DLESS"
#define GREAT "GREAT"
#define DGREAT "DGREAT"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft.h"
# include <fcntl.h>
#include <signal.h>

extern int	global_exit;

typedef struct s_cmd
{
	char			**words;
	char			**redirects;
	char			**here_docs;
	int				pipes;
	int				fd_out;
	int				fd_in;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_tkn
{
	char	***cmd;
	char	***cmd_lex;
	char	*line;
	char	**lexemas;
	char	**tokens;
	int		tkn_count;
	char	**envp;
	int		envp_count;
	char	**path;
	int		path_count;
	char	*path_0;
	char	*logname;
	int		cmd_count;
	int		len;
	char	**amb_v;
	int		amb_v_count;
	int		exp_start;
	int		exp_flag;
	int		exit_signal;
	int		i_cmd;
	int		words;
	int		pipes;
	int		redirects;
	int		here_docs;
}	t_tkn;

void	printf_cmd_tab(t_cmd **cmd_tab);

int		get_prompt(t_tkn *tkn, t_cmd **cmd_tab);

int		token_analysis(t_tkn *tkn);

void	lexical_analysis(t_tkn *tkn);

int		sintax_analysis(t_tkn *tkn);

void	create_cmd_tab(t_tkn *tkn, t_cmd **cmd_tab);

void	create_node(t_tkn *tkn,t_cmd **cmd_tab, int start, int end);

void	expansion(t_tkn *tkn, t_cmd **cmd_tab);

int		expansion_tilde(t_tkn *tkn, char **token, int j);

void	expansion_envp(t_tkn *tkn);

int		prepare_envp(t_tkn **tkn, char **quote, int j);

int		join_token(char **quote, char **temp, char **exp_envp, char **temp_2);

int		prepare_quote(t_tkn **tkn, char **token, int j);

void	quoted_envp(char **tkn);

void	redirection(t_cmd **cmd_tab);



int		cmd_word(t_tkn *tkn, int i);

int		exec_cmd_path_ck(t_tkn *tkn, int i);

void	exec_cmd_tab(t_tkn *tkn);

//void	exec_simple_cmd(t_tkn *tkn, int i);

int		cmd_setup(t_tkn *tkn, int i);

void	cmd_not_found(t_tkn *tkn, int i);

void	exec_cmd_pipe(t_tkn *tkn);

void	exec_cmd_d_great(t_tkn *tkn);

void	exec_cmd_d_less(t_tkn *tkn, int i);

int		built_in_cmd(t_tkn *tkn, int i);

void	exec_cmd_echo(t_tkn *tkn, int i);

void	exec_cmd_pwd(void);

void	exec_cmd_cd(t_tkn *tkn, int i);

void	exec_cmd_export(t_tkn *tkn, int i);

void	exec_cmd_unset(char ***envp, char *cmd_arg, int *count);

void	exec_cmd_env(t_tkn *tkn, int flag);

void	exec_cmd_exit(t_tkn *tkn, int i);

void	handle_signal_prompt(void);

void	handle_signal_parent(void);

void	handle_signal_child(void);

void	handle_signal_here_doc(void);

void	setup_error(char *arg, int flag);

void	exit_shell(t_tkn *tkn, t_cmd **cmd_tab);

void	exit_shell_quote(t_tkn *tkn, int i);

void	free_tab(char ***tab, int i);

#endif