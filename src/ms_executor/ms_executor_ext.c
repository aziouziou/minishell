/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:36:36 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:00 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_check_if_redir(t_redir *commands, int *status)
{
	t_redir	*redir;

	redir = commands;
	while (redir)
	{
		g_minishell.dup_in = dup(0);
		if (check_redirecrt(commands, status) != ERR_RET)
			return ;
		redir = redir->next;
	}
}

int	ms_system_cmd(t_cmd *commands)
{
	int	pid;
	int	status;
	int	statuss;

	pid = fork();
	status = 1;
	if (pid == 0)
	{
		if (check_redirecrt(commands->redir, &status) == ERR_RET)
			exit(0);
		exit(ms_print_command(commands->args));
	}
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		if (waitpid (-1, &statuss, 0) == -1)
			break ;
	}
	ms_check_file_status(status);
	if (WIFEXITED(statuss))
		g_minishell.exit_status = WEXITSTATUS(statuss);
	else if (WIFSIGNALED(statuss))
		ms_handle(statuss);
	return (1);
}

int	ms_open_in(char *filename, int *status)
{
	g_minishell.r_in = open(filename, O_RDONLY, 0644);
	if (g_minishell.r_in == -1)
	{
		ms_file_descriptor_error();
		return (ERR_RET);
	}
	*status = 0;
	dup2(g_minishell.r_in, 0);
	close(g_minishell.r_in);
	return (1);
}

void	ms_open_append(char *filename)
{
	g_minishell.w_out = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (g_minishell.w_out == -1)
	{
		dup2(g_minishell.dup_out, 1);
		close(g_minishell.w_out);
		ms_file_descriptor_error();
		return ;
	}
	dup2(g_minishell.w_out, 1);
	close(g_minishell.w_out);
}

int	ms_open_heredoc_file(char *filename, int *status)
{
	g_minishell.r_in = open(filename, O_RDONLY, 0644);
	if (g_minishell.r_in == -1)
	{
		ms_file_descriptor_error();
		return (ERR_RET);
	}
	unlink(filename);
	*status = 0;
	dup2(g_minishell.r_in, 0);
	close(g_minishell.r_in);
	return (1);
}
