/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:48:52 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:47 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_builtin_env(char **command)
{
	t_env	*env;

	env = g_minishell.env;
	if (*(command + 1))
	{
		g_minishell.exit_status = 1;
		ms_putstr_fd(ms_err_gen("env: ",*(command + 1), ": Too Many Argument \
			\n"), 2);
		return ;
	}
	while (env)
	{
		if (ms_strstr(env->value, "="))
			ms_putstr_fd(ms_strjoin(env->value, "\n"), 1);
		env = env->next;
	}
	g_minishell.exit_status = 0;
}

t_env	*ms_unset(char **cmd)
{
	t_env	*list;
	t_env	*prev;

	list = g_minishell.env;
	prev = g_minishell.env;
	if (!list)
		return (NULL);
	if (!*(cmd + 1))
		return (list);
	else
	{
		if (!ms_strcmp(prev->key, cmd[1]))
		{
			list = list->next;
			ms_add_garbage(&g_minishell.garbage, prev);
			return (list);
		}
	}
	cmd++;
	if (!*cmd)
		return (list);
	ms_env_line_remove(cmd, list);
	return (list);
}

t_env	*ms_env_line_remove(char **cmd, t_env *list)
{
	t_env	*tmp;
	t_env	*prev;

	list = g_minishell.env;
	tmp = g_minishell.env;
	prev = g_minishell.env;
	tmp = tmp->next;
	while (*(cmd))
	{
		tmp = list->next;
		prev = list;
		while (tmp)
		{
			if (!ms_strcmp(tmp->key, *cmd))
			{
				prev->next = tmp->next;
				break ;
			}
			tmp = tmp->next;
			prev = prev->next;
		}
		cmd++;
	}
	ms_add_garbage(&g_minishell.garbage, tmp);
	return (list);
}
