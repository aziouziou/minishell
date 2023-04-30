/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:30:32 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:39 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_add_garbage(t_garbage **garbage, void *garbage_ptr)
{
	t_garbage	*garbage_node;

	garbage_node = malloc(sizeof(t_garbage));
	if (!garbage_node)
		return ;
	garbage_node->garbage_ptr = garbage_ptr;
	garbage_node->next = *garbage;
	*garbage = garbage_node;
}

void	ms_free_garbage(t_garbage *garbage)
{
	t_garbage	*tmp;

	tmp = garbage;
	while (tmp)
	{
		printf("Freeing: %p\n", g_minishell.garbage);
		free(garbage->garbage_ptr);
		tmp = tmp->next;
	}
	free(tmp);
}
