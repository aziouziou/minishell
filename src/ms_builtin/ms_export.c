/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:07:44 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:53 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_export(char **command)
{
	char	*argument;
	char	*value;
	int		is_append;

	argument = NULL;
	value = NULL;
	is_append = 0;
	command++;
	if (*command != NULL)
		ms_export_new_arg(command, is_append, argument, value);
	else
		ms_get_export();
}

void	ms_add_to_env(char *key, char *value)
{
	if (!value)
		ms_add_env_line(&g_minishell.env, key, key);
	else
		ms_add_env_line(&g_minishell.env, key, ms_strjoin(key, \
			ms_strjoin("=", value)));
}

int	ms_export_new_arg(char **cmd, int is_append, char *key, char *val)
{
	while (*cmd)
	{
		if (ms_env_arg_error(cmd))
			return (ms_putstr_fd(ms_err_gen(ERR_EXP, *cmd, ERR_ID), 2), 365);
		if (ms_check_valid_var(ms_get_var(*cmd), 0) == -1)
			return (ms_putstr_fd(ms_err_gen(ERR_EXP, *cmd, ERR_ID), 2), 365);
		if (ms_check_append(*cmd))
			is_append = 1;
		key = ms_get_var(*cmd);
		if (ms_strchr(*cmd, '='))
			val = ms_strchr(*cmd, '=') + 1;
		if (is_append)
			key = ms_substr(key, 0, ms_strlen(key) - 1);
		if (ms_check_valid_var(ms_get_var(key), 1) == -2)
			return (ms_putstr_fd(ms_err_gen(ERR_EXP, \
				*cmd, ERR_ID), 2), ERR_RET);
		if (ms_check_inside_env(key))
			ms_add_to_env(key, val);
		else
			ms_update_env_var(key, val, is_append);
		is_append = 0;
		cmd++;
	}
	return (1);
}

int	ms_check_append(char *command)
{
	while (*command)
	{
		if (*command == '+' && *(command + 1) == '=')
			return (1);
		command++;
	}
	return (0);
}

char	*ms_get_var(char *arg)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = ms_strdup("");
	if (!arg)
		return (NULL);
	while (arg[i] != '=' && arg[i])
		i++;
	if (!buffer)
		return (NULL);
	buffer = malloc(sizeof(char) * (i + 1));
	ms_add_garbage(&g_minishell.garbage, buffer);
	i = 0;
	while (arg[i] != '=' && arg[i])
	{
		buffer[i] = arg[i];
		i++;
	}
	buffer[i] = 0;
	return (buffer);
}
