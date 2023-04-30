/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:35:16 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:53 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_env_size(void)
{
	int		i;
	t_env	*env;

	env = g_minishell.env;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	ms_print_exported(char **export)
{
	int		i;
	char	**spl;

	i = -1;
	while (export[++i])
	{
		spl = ms_split(export[i], '=');
		if (spl[1] != NULL || ms_strstr(spl[0], "="))
			printf("declare -x %s=\"%s\"\n", spl[0], spl[1]);
		else
			printf("declare -x %s\n", spl[0]);
	}
}
