/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:05:52 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:03 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_check_heredoc(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (tmp->next->type == 1 && tmp->next != NULL)
			{
				tmp->next->next->content = ms_strdup(ms_heredoc_ext(tmp->next));
				ms_open_heredoc(&tmp->next->next->content, \
					&tmp->next->next->type);
			}
			else
			{
				tmp->next->content = ms_strdup(ms_heredoc_ext(tmp->next));
				ms_open_heredoc(&tmp->next->content, &tmp->next->type);
			}
		}
		tmp = tmp->next;
	}
}

char	*ms_heredoc_ext(t_tokens *tokens)
{
	char		*buffer;
	t_tokens	*tmp;

	tmp = tokens;
	buffer = ms_strdup("");
	if (tmp->type == 1)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == 1)
			break ;
		if (tmp->type == 9)
			buffer = ms_strjoin(buffer, ms_strjoin("$", tmp->content));
		else
			buffer = ms_strjoin(buffer, tmp->content);
		tmp->content = ms_strdup("\0");
		tmp->type = 1;
		tmp = tmp->next;
	}
	return (buffer);
}

int	ms_open_heredoc(char **value, int *type)
{
	static int	id;

	id++;
	g_minishell.n_h = id;
	ms_child_heredoc(&value, type);
	return (1);
}

void	ms_child_heredoc(char ***value, int *type)
{
	char	*buffer;
	char	*filename;
	char	*input;
	int		fd;

	buffer = ms_strdup("");
	input = NULL;
	**value = ms_return_val(ms_strtrim(**value, " "));
	while (1)
	{
		input = readline("> ");
		ms_add_garbage(&g_minishell.garbage, input);
		if (!input || !ms_strcmp(**value, input))
			break ;
		else
			buffer = ms_strjoin(buffer, ms_strjoin(input, "\n"));
	}
	filename = ms_get_filename(ms_strjoin("/tmp/.heredoc", \
		ms_itoa(g_minishell.n_h)));
	**value = filename;
	fd = open (**value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	*type = 11;
	ms_putstr_fd(buffer, fd);
	close(fd);
}

char	*ms_return_val(char *value)
{
	char	*buffer;
	int		i;

	i = 0;
	while (value[i] && value[i] != ' ')
		i++;
	buffer = malloc(i + 1);
	ms_add_garbage(&g_minishell.garbage, buffer);
	i = 0;
	while (value[i] && value[i] != ' ')
	{
		buffer[i] = value[i];
		i++;
	}
	buffer[i] = 0;
	return (buffer);
}
