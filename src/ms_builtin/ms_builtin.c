/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:42:54 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:48 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_builtin(char **command, int *status)
{
	if (!ms_strcmp(*command, "cd"))
		ms_cd(command);
	if (!ms_strcmp(*command, "exit"))
		ms_exit(command);
	if (!ms_strcmp(*command, "env"))
		ms_builtin_env(command);
	if (!ms_strcmp(*command, "export"))
		ms_export(command);
	if (!ms_strcmp(*command, "echo"))
		ms_echo(command);
	if (!ms_strcmp(*command, "pwd"))
		ms_pwd();
	if (!ms_strcmp(*command, "unset"))
		g_minishell.env = ms_unset(command);
	*status = 0;
}

int	ms_check_builtin(char *command)
{
	if (!ms_strcmp(command, "echo") \
			|| !ms_strcmp(command, "cd") || !ms_strcmp(command, "export") \
			|| !ms_strcmp(command, "unset") || !ms_strcmp(command, "exit") \
			|| !ms_strcmp(command, "pwd") || !ms_strcmp(command, "env"))
		return (1);
	return (0);
}
