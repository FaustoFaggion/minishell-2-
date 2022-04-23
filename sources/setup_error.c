/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:50:37 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/20 09:57:31 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_error_cont_2(char *arg, int flag)
{
	if (flag == 8)
	{
		ft_putendl_fd("exit:\nexit: ", 2);
		ft_putendl_fd(arg, 2);
		ft_putendl_fd(": requer argumento numérico\n", 2);
		global_exit = 2;
	}
	if (flag == 9)
	{
		printf("bash: cd: número excessivo de argumentos\n");
		global_exit = 1;
	}
}

void	setup_error_cont(char *arg, int flag)
{
	if (flag == 4)
	{
		printf("bash: erro de sintaxe próximo ao token inesperado `newline'\n");
		global_exit = 2;
	}
	if (flag == 5)
	{
		printf("bash: erro de sintaxe próximo ao token inesperado `%s'\n", arg);
		global_exit = 2;
	}
	if (flag == 6)
	{
		printf("bash: export: `%s`: não é um identificador válido\n", arg);
		global_exit = 1;
	}
	if (flag == 7)
	{
		ft_putendl_fd("exit\nbash: exit: número excessivo de argumentos\n", 2);
		global_exit = 1;
	}
	setup_error_cont_2(arg, flag);
}

void	setup_error(char *arg, int flag)
{
	if (flag == 0)
	{
		write(1, arg, ft_strlen(arg));
		write(1, ": Command not found\n", 20);
		global_exit = 127;
	}
	if (flag == 1)
	{
		printf("bash: %s: Arquivo ou diretório inexistente\n", arg);
		global_exit = 1;
	}
	if (flag == 2)
	{
		write(2, "Quote missing\n", 14);
		global_exit = 10000000;
	}
	if (flag == 3)
	{
		printf("bash: erro de sintaxe próximo ao token inesperado '%s'\n", arg);
		global_exit = 2;
	}
	setup_error_cont(arg, flag);
}
