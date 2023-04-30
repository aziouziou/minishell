/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:53:47 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:00 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_redirecrt(t_redir *redir, int *status)
{
	int		len;

	len = ms_redir_count(redir);
	if (len > 0)
	{
		while (redir)
		{
			if (ms_check_redirection(redir->type, redir->filename, \
			status) == ERR_RET)
				return (ERR_RET);
			redir = redir->next ;
		}
	}
	return (1);
}

void	ms_check_file_status(int status)
{
	if (status)
	{
		dup2(g_minishell.dup_out, 1);
		close(g_minishell.dup_out);
	}
	else
	{
		dup2(g_minishell.dup_in, 0);
		dup2(g_minishell.dup_out, 1);
		close(g_minishell.dup_out);
		close(g_minishell.dup_in);
	}
}
