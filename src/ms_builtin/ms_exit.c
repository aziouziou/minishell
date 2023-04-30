/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:45:22 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:51 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_exit(char **command)
{
	char	*str;

	str = *(command + 1);
	if (*command && *(command + 1) == NULL)
	{
		ms_putstr_fd("exit\n", 2);
		exit (0);
	}
	command++;
	if (!ms_check_valid_num(str, *command))
		exit(255);
	if (*(command + 1) == NULL)
	{
		g_minishell.exit_status = ms_atoi(*command);
		printf("exit \n");
		exit (ms_atoi(*command));
	}
	if (*++command)
	{
		ms_putstr_fd(ms_err_gen("exit \nminishell: exit: ", \
			*command, "Too many arguments\n"), 2);
		return ;
	}
}

int	ms_check_valid_num(char *str, char *cmd)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ms_is_number(str[i]))
		{
			return (ms_putstr_fd(ms_err_gen("exit \nminishell: exit: ", cmd, \
							" numeric argument required\n"), 2), 0);
		}
	}
	return (1);
}

int	ms_is_number(char n)
{
	if (n < '0' || n > '9')
		return (0);
	return (1);
}
