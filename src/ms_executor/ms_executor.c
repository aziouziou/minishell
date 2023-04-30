/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:48:36 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:01 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_executor(t_cmd *commands, t_tokens *tokens)
{
	int	status;

	g_minishell.fdd = 0;
	status = 1;
	if (g_minishell.exit_status == 127)
		g_minishell.exit_status = 0;
	if (ms_check_one_command(commands, tokens, &status))
		return ;
	else
		ms_pipe_commands(commands, status);
}

int	ms_check_one_command(t_cmd *commands, t_tokens *tokens, int *status)
{
	if (ms_is_pipe(tokens) == 0)
	{
		g_minishell.dup_out = dup(1);
		if (*commands->args == NULL)
		{
			g_minishell.dup_in = dup(0);
			if (check_redirecrt(commands->redir, status) == ERR_RET)
				return (ms_check_file_status(*status), 1);
		}
		if (*commands->args != NULL)
		{
			if (ms_check_builtin(*commands->args))
			{
				g_minishell.dup_in = dup(0);
				if (check_redirecrt(commands->redir, status) == ERR_RET)
					return (ms_check_file_status(*status), 1);
				ms_builtin(commands->args, status);
			}
			else
				ms_system_cmd(commands);
		}
		return (ms_check_file_status(*status), 1);
	}
	return (0);
}

void	ms_pipe_commands(t_cmd *commands, int status_ext)
{
	pid_t	pid;
	int		status;

	status = 1;
	while (commands)
	{
		if (pipe(g_minishell.fd) < 0)
			return ;
		pid = fork();
		if (!ms_check_pid(pid))
			return ;
		else if (pid == 0)
			ms_child_process(commands, &status);
		close(g_minishell.fd[1]);
		if (g_minishell.fdd != 0)
			close(g_minishell.fdd);
		if (!commands->next)
			close(g_minishell.fd[0]);
		g_minishell.fdd = g_minishell.fd[0];
		commands = commands->next;
	}
	while (1)
		if (waitpid(-1, &status_ext, 0) == -1)
			break ;
	ms_signal_handler_2(&status_ext);
}

int	ms_check_pid(int pid)
{
	if (pid < 0)
	{
		close(g_minishell.fd[0]);
		close(g_minishell.fd[1]);
		close(g_minishell.fdd);
		while (1)
		{
			if (waitpid(-1, NULL, 0) == -1)
				break ;
		}
		return (ms_putstr_fd("minishell: fork: Resource temporarily \
			unavailable\n", 2), 0);
	}
	return (1);
}

void	ms_child_process(t_cmd *commands, int *status)
{
	close(g_minishell.fd[0]);
	if (g_minishell.fdd != 0)
	{
		dup2(g_minishell.fdd, 0);
		close(g_minishell.fdd);
	}
	if (commands->next != NULL)
	{
		close(g_minishell.fd[0]);
		dup2(g_minishell.fd[1], 1);
	}
	close(g_minishell.fd[1]);
	ms_check_if_redir(commands->redir, status);
	if (ms_check_builtin(*(commands->args)))
	{
		if (g_minishell.exit_status == 127)
			g_minishell.exit_status = 1;
		else
			g_minishell.exit_status = 0;
		ms_builtin(commands->args, status);
		exit(1);
	}
	else
		exit(ms_print_command(commands->args));
}
