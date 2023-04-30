/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:16:13 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:28 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	int	is_set(char const *s, char c);

char	*ms_strtrim(char const *input, char const *set)
{
	char		*str;
	long long	start;
	long long	end;

	if (!input || !set)
		return (NULL);
	start = 0;
	end = ms_strlen(input) - 1;
	while (is_set(set, input[start]))
		start++;
	while (is_set(set, input[end]) && end >= 0)
		end--;
	if (end < 0)
		return (ms_strdup(""));
	str = malloc(end - start + 2);
	if (!str)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, str);
	ms_strlcpy(str, input + start, end - start + 2);
	return (str);
}

static	int	is_set(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i++] == c)
			return (1);
	}
	return (0);
}
