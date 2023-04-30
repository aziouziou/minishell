/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:16:18 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:57 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_expander(t_tokens **tokens)
{
	int			i;
	t_tokens	*command;

	i = 0;
	command = *tokens;
	while (command)
	{
		if (command->type == DOLLAR)
			ms_expand_dollar(&command->content, i);
		else if (command->type == EXIT_STATUS)
			ms_expand_status(&command->content);
		else if (command->type == 11)
		{
			if (command->content[0] == '~' && command->content[1] == '\0')
				command->content = ms_strdup(getenv("HOME"));
		}
		command = command->next;
	}
}

void	ms_expand_dollar(char **command_value, int i)
{
	char	*cmd_val;
	t_env	*env;

	cmd_val = *command_value;
	env = g_minishell.env;
	while (env)
	{
		if (!ms_strcmp(env->key, cmd_val))
		{
			*command_value = ms_strstr(env->value, "=") + 1;
			break ;
		}
		else
			ms_update(cmd_val, &command_value);
		env = env->next;
		i++;
	}
	if (i == 0)
		*command_value = "\0";
}

void	ms_expand_status(char **command_value)
{
	*command_value = ms_itoa(g_minishell.exit_status);
}

void	ms_update(char *val, char ***value)
{
	if (val[0] == '0' && val[1] == '\0')
		**value = ms_strdup("minishell");
	else if (val[0] >= '1' && val[0] <= '9' && val[1] == '\0')
		**value = ms_strdup("\0");
	else
		**value = ms_strdup("\0");
}
