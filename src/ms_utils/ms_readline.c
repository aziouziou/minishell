/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:19:14 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:40 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_readline(void)
{
	char	*input;
	char	*prompt_return;

	ms_signals();
	prompt_return = ms_strdup("");
	input = readline(PROMPT);
	if (!input)
		ms_error("exit", 1);
	ms_add_garbage(&g_minishell.garbage, input);
	if (input && input[0])
		add_history(input);
	prompt_return = ms_prompt_return(ms_strtrim(input, " "));
	return (prompt_return);
}

char	*ms_prompt_return(char *input)
{
	char	*buffer;
	int		i;
	int		len;

	i = 0;
	len = ms_strlen(input) - 1;
	while (input[len] == ' ')
		len--;
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, buffer);
	while (i <= len)
	{
		buffer[i] = input[i];
		i++;
	}
	buffer[i] = '\0';
	free(input);
	return (buffer);
}
