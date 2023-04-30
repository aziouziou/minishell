/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:07:49 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:32 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_add_command(t_cmd **commands, t_tokens *tokens)
{
	char	*str;
	char	**str2;
	t_redir	*redir;

	str = ms_strdup("");
	redir = NULL;
	ms_add_redir(&redir, tokens);
	while (tokens)
	{
		if (tokens->type == WHITESPACE && tokens->next == NULL)
			break ;
		else if (tokens->type != REDIR_IN && tokens->type != REDIR_OUT \
				&& tokens->type != APPEND && tokens->type != HEREDOC)
			str = ms_strjoin(str, tokens->content);
		else
		{
			if (tokens->next->type == 1)
				tokens = tokens->next;
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	str2 = ms_split(str, '\t');
	ms_add_command_back(commands, str2, redir);
}

void	ms_add_command_back(t_cmd **commands, char **arg, t_redir *redir)
{
	t_cmd	*head;
	t_cmd	*new;

	new = ms_add_new_command(arg, redir);
	if (!*commands)
		*commands = new;
	else
	{
		head = *commands;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

t_cmd	*ms_add_new_command(char **arg, t_redir *redir)
{
	t_cmd	*new_command;

	new_command = (t_cmd *)malloc(sizeof(t_cmd));
	ms_add_garbage(&g_minishell.garbage, new_command);
	if (new_command != NULL)
	{
		new_command->args = arg;
		new_command->redir = redir;
		new_command->r_in = 0;
		new_command->w_out = 1;
		new_command->next = NULL;
	}
	return (new_command);
}

t_cmd	*ms_free_commands(t_cmd **commands)
{
	t_cmd	*tmp;
	t_redir	*redir;

	while ((*commands))
	{
		while ((*commands)->redir)
		{
			redir = (*commands)->redir;
			(*commands)->redir = (*commands)->redir->next;
			free(redir);
		}
		tmp = (*commands);
		(*commands) = (*commands)->next;
		free(tmp);
	}
	return (NULL);
}

int	ms_check_first_command(char *str, int status)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
			{
				status = 1;
				break ;
			}
		}
		if (status == 0)
			return (1);
	}
	return (0);
}
