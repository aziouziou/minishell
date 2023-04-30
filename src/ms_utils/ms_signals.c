/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:20:22 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:41 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_signals(void)
{
	signal(SIGINT, ms_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ms_signal_handler(int sig)
{
	(void)sig;
	rl_catch_signals = 0;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ms_signal_handler_2(int *statuss)
{
	if (WIFEXITED(statuss))
		g_minishell.exit_status = WEXITSTATUS(statuss);
	else if (WIFSIGNALED(statuss))
		g_minishell.exit_status = 128 + WTERMSIG(statuss);
}
