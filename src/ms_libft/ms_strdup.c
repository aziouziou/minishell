/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:18:13 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:22 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_strdup(const char *s)
{
	char	*dup;
	size_t	i;
	size_t	len_str;

	i = 0;
	len_str = ms_strlen(s) + 1;
	dup = malloc(len_str);
	if (!dup)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, dup);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
