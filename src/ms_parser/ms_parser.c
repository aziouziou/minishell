/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:55:11 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:33 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*ms_parser(t_tokens *tokens)
{
	t_cmd		*command;
	t_tokens	*tokens_copy;
	t_tokens	*tmp;

	command = NULL;
	tmp = tokens;
	tokens_copy = NULL;
	while (tmp)
	{
		while (tmp->type != PIPE && tmp->next != NULL)
		{
			ms_add_token(&tokens_copy, tmp->content, tmp->type);
			tmp = tmp->next;
		}
		if (tmp->next == NULL)
			ms_add_token(&tokens_copy, tmp->content, tmp->type);
		ms_add_command(&command, tokens_copy);
		ms_free_tokens(&tokens_copy);
		tmp = tmp->next;
	}
	ms_free_tokens(&tmp);
	ms_free_tokens(&tokens_copy);
	return (command);
}
