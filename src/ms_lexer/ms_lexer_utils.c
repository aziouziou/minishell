/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:59:45 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:06 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_add_dollar_sign(t_tokens **tokens, char input)
{
	char	*special_chars;
	char	*str;

	special_chars = ms_strdup(" ()+-*/.,:|$^`~\'\"\\");
	str = malloc(2);
	if (!str)
		return (ERR_RET);
	ms_add_garbage(&g_minishell.garbage, str);
	str[0] = input;
	str[1] = 0;
	while (*special_chars)
	{
		if (input == *special_chars)
		{
			ms_add_token(tokens, ms_strjoin("$", str), WORD);
			return (1);
		}
		special_chars++;
	}
	return (ERR_RET);
}

char	*ms_in_single_quotes(t_tokens **tokens, char *input, char quote, int i)
{
	char	*buffer;

	buffer = 0;
	if (i == 0 && *(input + 1) == '\0')
	{
		ms_add_token(tokens, "\t", WORD);
		return (" ");
	}
	buffer = malloc(sizeof(char) * (i + 1));
	if (!buffer)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, buffer);
	if (!buffer)
		return (NULL);
	i = 0;
	while (input[i] && input[i] != quote)
	{
		buffer[i] = input[i];
		i++;
	}
	buffer[i] = 0;
	ms_add_token(tokens, buffer, WORD);
	return (NULL);
}

char	*ms_in_double_quotes(t_tokens **tokens, char *input, char quote, int i)
{
	char	*buffer;

	buffer = ms_strdup("");
	buffer = malloc(sizeof(char) * (i + 1));
	if (!buffer)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, buffer);
	if (i == 0 && *(input + 1) == '\0')
	{
		ms_add_token(tokens, "\t", WORD);
		return (" ");
	}
	i = 0;
	while (input[i] && input[i] != quote)
	{
		buffer[i] = input[i];
		i++;
	}
	buffer[i] = 0;
	ms_add_quotes(tokens, buffer, quote);
	return (NULL);
}

void	ms_add_quotes( t_tokens **tokens, char *buffer, char quote)
{
	while (*buffer != 0)
	{
		buffer = ms_check_word(tokens, buffer, "$");
		if (quote == '\"')
			buffer = ms_check_env(tokens, buffer);
		buffer++;
	}
}
