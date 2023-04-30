/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouazi <abouazi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 13:39:33 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 02:31:42 by abouazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_lexer(t_tokens **tokens, char *input)
{
	while (*input)
	{
		input = ms_check_whitespace(tokens, input);
		input = ms_check_word(tokens, input, " $<>|\'\"\f\n\r\t\v");
		input = ms_check_pipe(tokens, input);
		input = ms_check_redir(tokens, input);
		input = ms_check_env(tokens, input);
		input = ms_check_double_quote(tokens, input, '\"');
		if (!input)
			return (ERR_RET);
		input = ms_check_single_quote(tokens, input, '\'');
		if (!input)
			return (ERR_RET);
		input++;
	}
	return (1);
}

char	*ms_check_whitespace(t_tokens **tokens, char *input)
{
	int	result;

	result = 0;
	while (*input && ms_strchr(" \f\n\r\t\v", *input))
	{
		input++;
		result++;
	}
	if (result != 0)
		ms_add_token(tokens, "\t", WHITESPACE);
	return (input);
}

char	*ms_check_word(t_tokens **tokens, char *input, char *special_chars)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = ms_strdup("");
	while (!ms_strchr(special_chars, input[i]))
		i++;
	buffer = malloc(sizeof(char) * i);
	if (!buffer)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, buffer);
	i = 0;
	while (*input && !ms_strchr(special_chars, *input))
		buffer[i++] = *input++;
	if (i != 0)
	{
		buffer[i] = 0;
		if (ms_strlen(special_chars) == 12 || ms_strlen(special_chars) == 1)
			ms_add_token(tokens, buffer, WORD);
		else
			ms_add_token(tokens, buffer, DOLLAR);
		return (input - 1);
	}
	return (input);
}

char	*ms_check_pipe(t_tokens **tokens, char *input)
{
	if (*input == '|')
		ms_add_token(tokens, "|", PIPE);
	return (input);
}

char	*ms_check_redir(t_tokens **tokens, char *input)
{
	if (*input == '>' && input[1] == '>')
	{
		ms_add_token(tokens, ">>", APPEND);
		input++;
	}
	else if (*input == '>')
		ms_add_token(tokens, ">", REDIR_OUT);
	else if (*input == '<' && input[1] == '<')
	{
		ms_add_token(tokens, "<<", HEREDOC);
		input++;
	}
	else if (*input == '<')
		ms_add_token(tokens, "<", REDIR_IN);
	return (input);
}
