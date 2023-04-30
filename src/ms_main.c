/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:10:48 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:42 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell	g_minishell = {0};

int	main(int argc, char *argv[], char *envp[])
{
	if ((argc > 1 && argv) || !envp)
		ms_error(ERR_ARG, 0);
	ms_run(envp);
	return (0);
}

void	ms_run(char *envp[])
{
	char		*input;
	t_cmd		*commands;
	t_tokens	*tokens;

	input = ms_strdup("");
	tokens = NULL;
	g_minishell.s_h = 0;
	ms_init_env(envp);
	ms_launch(&tokens, &commands, input);
	ms_free_garbage(g_minishell.garbage);
}
