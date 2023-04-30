/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_ext_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouazi <abouazi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:38:31 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 02:39:15 by abouazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_handle(int c)
{
	if (c == 3)
		ms_putstr_fd("QUIT", 2);
	write(1, "\n", 1);
	g_minishell.exit_status = 128 + WTERMSIG(c);
}

int	ms_print_command(char **command)
{
	char	*path;
	char	**splited_path;

	signal(SIGQUIT, SIG_DFL);
	path = ms_get_path();
	if (!path)
		splited_path = ms_split("", ':');
	else
		splited_path = ms_split(path, ':');
	if (!access(*command, X_OK))
		path = *command;
	else if (ms_strchr(*command, '/'))
		path = *command;
	else
	{
		while (*splited_path)
		{
			path = ms_strjoin(*splited_path, ms_strjoin("/", command[0]));
			if (!access(path, X_OK))
				break ;
			splited_path++;
		}
	}
	return (ms_execve(path, command));
}

int	ms_execve(char *path, char **command)
{
	execve(path, command, ms_export_env(g_minishell.env));
	ms_check_exit_status(*command);
	if (errno == ENOENT || errno == EFAULT)
		return (127);
	else if (errno == EACCES)
		return (126);
	return (ERR_RET);
}

void	ms_check_exit_status(char *command)
{
	if (errno == ENOENT || errno == EFAULT)
		ms_putstr_fd(ms_err_gen("minishell : ", command,
				": command not found \n"), 2);
	else if (errno == EACCES)
		ms_putstr_fd(ms_err_gen("minishell : ", command, ": Permission \
			denied\n"), 2);
	else
		ms_putstr_fd("error ...\n", 2);
}

char	**ms_export_env(t_env *env)
{
	char	**exported_env;
	int		i;
	int		len;
	t_env	*tmp;

	i = 0;
	len = 0;
	tmp = env;
	exported_env = NULL;
	while (tmp && ++len)
		tmp = tmp->next;
	exported_env = malloc(sizeof(char *) * len++);
	if (!exported_env)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, exported_env);
	while (env)
	{
		exported_env[i++] = env->value;
		env = env->next;
	}
	exported_env[i] = NULL;
	return (exported_env);
}
