/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokens_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:58:42 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:09 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_add_token(t_tokens **tokens, char *content, int type)
{
	t_tokens	*head;
	t_tokens	*new;

	new = ms_new_token(type, content);
	if (!*tokens)
		*tokens = new;
	else
	{
		head = *tokens;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

t_tokens	*ms_new_token(int type, char *content)
{
	t_tokens	*new_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	ms_add_garbage(&g_minishell.garbage, new_token);
	if (new_token != NULL)
	{
		new_token->content = content;
		new_token->type = type;
		new_token->next = NULL;
	}
	return (new_token);
}

t_tokens	*ms_free_tokens(t_tokens **tokens)
{
	t_tokens	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp);
	}
	return (NULL);
}

void	ms_print_tokens(t_tokens **tokens)
{
	int			i;
	t_tokens	*tmp;

	i = 0;
	tmp = *tokens;
	while (tmp)
	{
		printf("Token [%d] content is : %s\n", i, tmp->content);
		tmp = tmp->next;
		i++;
	}
}
