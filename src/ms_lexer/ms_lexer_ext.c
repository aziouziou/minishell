/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouazi <abouazi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:47:00 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 02:28:51 by abouazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_check_env(t_tokens **tokens, char *input)
{
	char	*buffer;

	if (*input == '$')
	{
		if (ms_add_dollar_sign(tokens, input[1]) != ERR_RET)
			return (input + 1);
		if (input[1] == '?')
			return (ms_add_token(tokens, "$?", EXIT_STATUS), input + 1);
		else if (*input && input[1] >= '0' && input[1] <= '9')
		{
			buffer = malloc(sizeof(char) * 2);
			if (!buffer)
				return (NULL);
			ms_add_garbage(&g_minishell.garbage, buffer);
			buffer[0] = input[1];
			buffer[1] = 0;
			return (ms_add_token(tokens, buffer, DOLLAR), input + 1);
		}
		else if (*(input + 1))
			return (ms_check_word(tokens, ++input, SPECIAL_CHARS));
		else
			ms_add_token(tokens, "$", WORD);
	}
	return (input);
}

char	*ms_check_double_quote(t_tokens **tokens, char *input, char quote)
{
	int		i;

	i = 0;
	if (*input == quote)
	{
		input++;
		if (ms_strchr(input, quote))
		{
			while (input[i] != quote)
				i++;
			ms_in_double_quotes(tokens, input, quote, i);
			return (ms_strchr(input, quote));
		}
		else
		{
			return (ms_putstr_fd("minishell: unclosed  quotes\n", 2), \
			g_minishell.exit_status = 258, NULL);
		}
	}
	return (input);
}

char	*ms_check_single_quote(t_tokens **tokens, char *input, char quote)
{
	int		i;

	i = 0;
	if (*input == quote)
	{
		input++;
		if (ms_strchr(input, quote))
		{
			while (input[i] != quote)
				i++;
			ms_in_single_quotes(tokens, input, quote, i);
			return (ms_strchr(input, quote));
		}
		else
			return (ms_putstr_fd("minishell: unclosed quotes.\n", 2), \
			g_minishell.exit_status = 258, NULL);
	}
	return (input);
}
