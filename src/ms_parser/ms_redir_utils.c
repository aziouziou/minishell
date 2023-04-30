/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:57:33 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:34 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_check_redirection(int type, char *filename, int *status)
{
	if (type == REDIR_OUT)
		ms_open_redir_out(filename, status);
	else if (type == APPEND)
		ms_open_append(filename);
	else if (type == REDIR_IN)
	{
		if (ms_open_in(filename, status) == ERR_RET)
			return (ERR_RET);
	}
	else if (type == HEREDOC && g_minishell.s_h != 1)
	{
		if (ms_open_heredoc_file(filename, status) == ERR_RET)
			return (ERR_RET);
	}
	return (1);
}

int	ms_redir_count(t_redir *redir)
{
	int		i;

	i = 0;
	while (redir)
	{
		i++;
		redir = redir->next ;
	}
	return (i);
}
