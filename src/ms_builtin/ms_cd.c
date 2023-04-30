/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:37:34 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:49 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_cd(char **command)
{
	char	*this_path;

	this_path = ms_getcwd();
	if (*(command + 1) != NULL )
	{
		if (!ms_strcmp(*(command + 1), "."))
		{
			if (chdir(this_path) == -1)
				ms_putstr_fd(ERR_FILE_DIR, 2);
			return ;
		}
	}
	if (*command && (*(command + 1) == NULL || !ms_strcmp(*(command + 1), "~")))
	{
		chdir(getenv("HOME"));
		ms_change_pwd(this_path);
	}
	else if (*command && *(command + 1)[0] == '-')
		ms_switch_cd();
	else
		ms_cd_plus(*(command + 1), this_path);
}

void	ms_cd_plus(char *cmd, char *path)
{
	if (chdir(cmd) == -1)
		ms_check_folder (cmd);
	else
		ms_change_pwd(path);
}

void	ms_switch_cd(void)
{
	char		path[PATH_MAX];
	static int	status;
	t_env		*env;

	env = g_minishell.env;
	while (env)
	{
		if (!ms_strcmp(env->key, "OLDPWD"))
			status = 1;
		env = env->next;
	}
	if (status == 0)
	{
		ms_putstr_fd("minishell : cd: OLDPWD not set\n", 2);
		return ;
	}
	else
	{
		ms_switcher();
		getcwd(path, PATH_MAX);
		printf("%s\n", path);
	}
}

void	ms_switcher(void)
{
	char		*old;
	char		*new;
	static int	is_switch;
	t_env		*temp;

	temp = g_minishell.env;
	while (temp)
	{
		if (!ms_strcmp(temp->key, "PWD"))
			new = ms_strstr(temp->value, "=") + 1;
		if (!ms_strcmp(temp->key, "OLDPWD"))
			old = ms_strstr(temp->value, "=") + 1;
		temp = temp->next;
	}
	if (is_switch == 0)
	{
		chdir(old);
			is_switch = 1;
	}
	else
	{
		chdir(new);
		is_switch = 0;
	}
}

void	ms_change_pwd(char *last_cmd)
{
	t_env	*env;
	bool	status_old;
	bool	status_pwd;

	status_old = true;
	status_pwd = true;
	env = g_minishell.env;
	while (env)
	{
		if (!ms_strcmp(env->key, "PWD"))
		{
			env->value = ms_strdup(ms_strjoin("PWD=", ms_getcwd()));
			status_pwd = false;
		}
		if (!ms_strcmp(env->key, "OLDPWD") && last_cmd != NULL)
		{
			env->value = ms_strdup(ms_strjoin("OLDPWD=", last_cmd));
			status_old = false;
		}
		env = env->next;
	}
	ms_add_pwd_env(status_pwd, status_old, last_cmd);
}
