/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:47:22 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:35 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_add_redir(t_redir **redir, t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT \
				|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (tokens->next->type == 1)
				ms_add_new_redir(redir, ms_strdup(tokens->next->next->content), \
					tokens->type);
			else
				ms_add_new_redir(redir, ms_strdup(tokens->next->content), \
					tokens->type);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
}

void	ms_add_new_redir(t_redir **redir, char *value, int type)
{
	t_redir	*head;
	t_redir	*new;

	new = ms_create_new_redir(type, value);
	if (!*redir)
		*redir = new;
	else
	{
		head = *redir;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

t_redir	*ms_create_new_redir(int type, char *val)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	ms_add_garbage(&g_minishell.garbage, new_redir);
	if (new_redir != NULL)
	{
		new_redir->filename = val;
		new_redir->type = type;
		new_redir->next = NULL;
	}
	return (new_redir);
}

void	ms_open_redir_out(char *filename, int *status)
{
	g_minishell.w_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (g_minishell.w_out == -1)
	{
		ms_file_descriptor_error();
		return ;
	}
	*status = 0;
	dup2(g_minishell.w_out, 1);
	close(g_minishell.w_out);
}
