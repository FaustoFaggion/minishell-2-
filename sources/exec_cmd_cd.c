/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:14:38 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/28 07:25:35 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_old_pwd_cont(t_tkn *tkn, char *old_dir)
{
	int		x;
	char	**temp;

	temp = tkn->envp;
	tkn->envp = NULL;
	tkn->envp = (char **)malloc(sizeof(char *) * (tkn->envp_count + 2));
	x = 0;
	while (temp[x] != NULL)
	{
		tkn->envp[x] = temp[x];
		x++;
	}
	tkn->envp[x] = ft_strjoin("OLDPWD=", old_dir);
	tkn->envp[++x] = NULL;
	tkn->envp_count++;
	free(temp);
}

static void	setup_old_pwd(t_tkn *tkn, char *old_dir)
{
	int		x;
	char	*swap;

	x = 0;
	while (tkn->envp[x] != NULL)
	{
		if (ft_strncmp(tkn->envp[x], "OLDPWD=", 7) == 0)
		{
			swap = tkn->envp[x];
			tkn->envp[x] = ft_strjoin("OLDPWD=", old_dir);
			free(swap);
			break ;
		}
		x++;
	}
	setup_old_pwd_cont(tkn, old_dir);
}

static void	setup_pwd(t_tkn *tkn)
{
	int		x;
	char	dir[1024];
	char	*swap;

	x = 0;
	while (tkn->envp[x] != NULL)
	{
		if (ft_strncmp(tkn->envp[x], "PWD=", 4) == 0)
		{
			getcwd(dir, sizeof(dir));
			swap = tkn->envp[x];
			tkn->envp[x] = ft_strjoin("PWD=", dir);
			free(swap);
			break ;
		}
		x++;
	}
}

static int	check_error(t_cmd **s_cmd)
{
	if ((*s_cmd)->words[2] != NULL)
	{
		setup_error((*s_cmd)->words[2], 9);
		return (1);
	}
	else
	{
		if (chdir((*s_cmd)->words[1]) == -1)
		{
			setup_error((*s_cmd)->words[1], 1);
			return (1);
		}
	}
	return (0);
}

void	exec_cmd_cd(t_cmd **s_cmd, t_tkn *tkn)
{
	char	old_dir[1024];
	char	*user;
	char	*user_path;

	user = getenv("USER");
	getcwd(old_dir, sizeof(old_dir));
	if ((*s_cmd)->words[1] == NULL)
		chdir("/home");
//	else if (ft_strncmp((*s_cmd)->words[1], "~\0", 2) == 0
//			|| ft_strncmp((*s_cmd)->words[1], "~/", 2) == 0)
//		chdir("/home");
	else if (ft_strncmp((*s_cmd)->words[1], "-\0", 2) == 0)
	{
		user_path = ft_strjoin("/home/", user);
		chdir(user_path);
		free(user_path);
	}
	else if (check_error(s_cmd) == 1)
		return ;
	setup_pwd(tkn);
	setup_old_pwd(tkn, old_dir);
}
