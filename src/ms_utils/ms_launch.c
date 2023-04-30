/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:38:47 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:39 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_launch(t_tokens **tokens, t_cmd **commands, char *input)
{
	while (1)
	{
		input = ms_readline();
		if (!input || !ms_is_whitespace(input))
			continue ;
		if (ms_lexer(tokens, input) == ERR_RET
			|| ms_check_syntax(*tokens) == ERR_RET)
		{
			ms_free_tokens(tokens);
			continue ;
		}
		ms_check_heredoc(tokens);
		ms_expander(tokens);
		*commands = ms_parser(*tokens);
		ms_executor(*commands, *tokens);
		ms_wipe(tokens, commands, input);
	}
	rl_clear_history();
}

void	ms_wipe(t_tokens **tokens, t_cmd **commands, char *input)
{
	unlink("/tmp/.heredoc");
	if (!tokens || !input)
		return ;
	ms_free_tokens(tokens);
	ms_free_commands(commands);
	free(input);
}
