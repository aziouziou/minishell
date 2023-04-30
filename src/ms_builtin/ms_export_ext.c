/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:33:52 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:52 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_check_valid_var(char *arg, int is_equal)
{
	while (*arg)
	{
		if (is_equal)
		{
			if (!ms_isalnum(*arg) && (*arg != '_'))
				return (-2);
		}
		if (!ms_isalnum(*arg) && (*arg != '_' && *arg != '+'))
			return (-1);
		arg++;
	}
	return (1);
}

int	ms_check_inside_env(char *arg)
{
	t_env	*env;

	env = g_minishell.env;
	while (env)
	{
		if (!ms_strcmp(env->key, arg))
			return (0);
		env = env->next;
	}
	return (1);
}

void	ms_update_env_var(char *var, char *val, int is_append)
{
	char	*temp_var;
	t_env	*env;

	env = g_minishell.env;
	if (!val)
		temp_var = var;
	else
		temp_var = ms_strdup(ms_strjoin(ms_strjoin(var, "="), val));
	if (!ms_strstr(temp_var, "="))
		return ;
	while (env)
	{
		if (!ms_strcmp(env->key, var))
		{
			if (is_append)
				env->value = ms_strjoin(env->value, val);
			else
				env->value = temp_var;
			break ;
		}
		env = env->next;
	}
}

void	ms_get_export(void)
{
	char	**str;
	int		i;
	t_env	*env;

	i = 0;
	str = NULL;
	env = g_minishell.env;
	while (env)
	{
		i++;
		env = env->next;
	}
	str = malloc(sizeof(char *) * i + 1);
	if (!str)
		return ;
	ms_add_garbage(&g_minishell.garbage, str);
	i = 0;
	env = g_minishell.env;
	while (env)
	{
		str[i++] = env->value;
		env = env->next;
	}
	str[i] = 0;
	ms_print_export(str);
}

void	ms_print_export(char **str)
{
	char	**export;
	int		i;
	char	*variable;

	i = 0;
	export = str;
	variable = NULL;
	while (i <= ms_env_size() && export[i + 1])
	{
		if (export[i][0] > export[i + 1][0])
		{
			variable = export[i + 1];
			export[i + 1] = export[i];
			export[i] = variable;
			i = 0;
		}
		else
			i++;
	}
	ms_print_exported(export);
}
