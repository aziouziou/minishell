/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:26:53 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:08 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_check_syntax(t_tokens *tokens)
{
	if (ms_pipe_status(tokens) == ERR_RET || ms_redir_check(tokens) == ERR_RET)
		return (ERR_RET);
	return (1);
}

int	ms_pipe_status(t_tokens *tokens)
{
	t_tokens	*input;

	input = tokens;
	if (input->type == PIPE)
		return (ms_putstr_fd(ms_err_gen(ERR_TOKEN, input->content, "\n"), \
			2), ERR_RET);
	while (input)
	{
		if (input->type == PIPE)
		{
			input = input->next;
			if (input)
			{
				while (input->type == WHITESPACE && input->next != NULL)
					input = input->next;
				if (input->type == PIPE)
					return (ms_putstr_fd(ms_err_gen(ERR_TOKEN, \
						input->content, "\n"), 2), ERR_RET);
			}
		}
		else
			input = input->next;
	}
	return (ms_check_pipe_is_last(tokens));
}

int	ms_check_pipe_is_last(t_tokens *tokens)
{
	char		*tmp;
	int			input_type;
	t_tokens	*input;

	input = tokens;
	while (input)
	{
		tmp = input->content;
		input_type = input->type;
		input = input->next;
	}
	if (tmp[0] == '|' && input_type == 2)
		return (ms_putstr_fd(ms_err_gen(ERR_TOKEN, tmp, "\n"), 2), ERR_RET);
	return (1);
}

int	ms_redir_check(t_tokens *tokens)
{
	char		*buffer;
	int			tmp_red;
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		buffer = tmp->content;
		tmp_red = tmp->type;
		if (tmp->next)
		{
			if (ms_check_redir_error(buffer, tmp_red, tmp) == ERR_RET)
				return (ERR_RET);
		}
		else if ((!ms_strcmp(buffer, "<") || !ms_strcmp(buffer, "<<") \
		|| !ms_strcmp(buffer, ">") || !ms_strcmp(buffer, ">>")) \
		&& (tmp_red >= 3 && tmp_red <= 6))
			return (ms_putstr_fd(ms_err_gen(ERR_NEWLINE, NULL, \
				"\n"), 2), ERR_RET);
		tmp = tmp->next;
	}
	return (1);
}
