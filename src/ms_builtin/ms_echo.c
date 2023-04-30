/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:11:12 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:50 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	search_n(char *s);

int	ms_echo(char **command)
{
	int		status;
	int		j;

	j = 0;
	status = 0;
	if (command[1] == NULL && ms_strcmp(*command, "$"))
		return (printf("\n"), ERR_RET);
	command++;
	ms_check_newline(command, status, j);
	g_minishell.exit_status = 0;
	return (1);
}

void	ms_check_newline(char **str, int status, int j)
{
	if (ms_strstr(*str, "-n") && search_n(*str))
	{
		str++;
		while (*str)
		{
			if (!ms_check_first_command(*str, status))
				break ;
			str++;
		}
		while (*str)
		{
			printf("%s",*str);
			if (*++str)
				printf(" ");
		}
	}
	else
	{
		while (str[j])
			ms_putstr_fd(ms_strjoin(str[j++], " "), 1);
		printf("\n");
	}
}

static int	search_n(char *s)
{
	int	i;

	i = -1;
	if (ms_strlen(&(s[++i])) == 0)
		return (1);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}
