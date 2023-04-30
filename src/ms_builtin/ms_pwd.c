/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:24:02 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:55 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_pwd(void)
{
	printf("%s\n", ms_getcwd());
}

char	*ms_getcwd(void)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	return (ms_strdup(path));
}

void	ms_add_pwd_env(int status_pwd, int status_old, char *last_cmd)
{
	if (status_pwd)
		ms_new_pwd_env_back(&g_minishell.env, ms_strdup("PWD"), \
				ms_strdup(ms_strjoin("PWD=", ms_getcwd())));
	if (status_old && last_cmd != NULL)
		ms_new_pwd_env_back(&g_minishell.env, ms_strdup("OLDPWD"), \
				ms_strdup(ms_strjoin("OLDPWD=", last_cmd)));
}

void	ms_new_pwd_env_back(t_env **env, char *key, char *value)
{
	t_env	*head;
	t_env	*new;

	new = ms_new_env_line(key, value);
	if (!*env)
		*env = new;
	else
	{
		head = *env;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

int	ms_check_folder(char *name)
{
	DIR	*dirs;

	errno = 0;
	dirs = opendir(name);
	if (!name)
		return (ERR_RET);
	if (dirs == NULL)
	{
		g_minishell.exit_status = 1;
		if (errno == 13)
			printf("permission denied\n");
		if (errno == ENOENT)
			printf("Directory does not exist\n");
		if (errno == ENOTDIR)
			printf("is not a directory\n");
		return (ERR_RET);
	}
	return (1);
}
