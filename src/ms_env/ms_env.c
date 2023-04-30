/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 02:38:25 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:56 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_init_env(char *envp[])
{
	char	**str;
	char	ab_path[1024];
	int		i;

	i = 0;
	if (!*envp)
	{
		getcwd(ab_path, 1024);
		ms_add_env_line(&g_minishell.env, "PATH", ms_strjoin("PATH=", \
			STD_PATH));
		ms_add_env_line(&g_minishell.env, "PWD", ms_strjoin("PWD=", ab_path));
		ms_add_env_line(&g_minishell.env, "SHLVL", "SHLVL=1");
		return ;
	}
	while (envp[i])
	{
		str = ms_split(envp[i], '=');
		if (ms_strcmp(*str, "OLDPWD"))
			ms_add_env_line(&g_minishell.env, *str, envp[i]);
		i++;
	}
	ms_shell_level(envp);
}

void	ms_add_env_line(t_env **ms_env, char *key, char *value)
{
	t_env	*head;
	t_env	*new_env_line;

	new_env_line = ms_new_env_line(key, value);
	if (!*ms_env)
		*ms_env = new_env_line;
	else
	{
		head = *ms_env;
		while (head->next)
			head = head->next;
		head->next = new_env_line;
	}
}

t_env	*ms_new_env_line(char *key, char *value)
{
	t_env	*new_env_line;

	new_env_line = (t_env *)malloc(sizeof(t_env));
	if (!new_env_line)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, new_env_line);
	if (new_env_line != NULL)
	{
		new_env_line->key = key;
		new_env_line->value = value;
		new_env_line->next = NULL;
	}
	return (new_env_line);
}

void	ms_shell_level(char *envp[])
{
	char	*str;
	int		current_shlvl;
	int		i;
	t_env	*ms_env;

	i = 0;
	current_shlvl = 0;
	ms_env = g_minishell.env;
	while (envp[i])
	{
		if (ms_strnstr(envp[i], "SHLVL", ms_strlen(envp[i])))
			current_shlvl = ms_atoi(ms_strnstr(envp[i], "SHLVL", \
			ms_strlen(envp[i] +1)) + 6);
		i++;
	}
	while (ms_env)
	{
		if (ms_strnstr("SHLVL", ms_env->key, 6))
		{
			str = ms_strjoin("SHLVL=", ms_itoa(current_shlvl + 1));
			ms_env->value = str;
			break ;
		}
		ms_env = ms_env->next;
	}
}

char	*ms_get_path(void)
{
	t_env	*env;

	env = g_minishell.env;
	while (env)
	{
		if (ms_strstr(env->key, "PATH"))
			return (ms_strstr(env->value, "=") + 1);
		env = env->next;
	}
	return (NULL);
}
