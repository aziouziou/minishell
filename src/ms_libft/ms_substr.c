/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:18:58 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:30 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	length;
	char	*str;

	if (!s)
		return (NULL);
	length = ms_strlen(s);
	if (start >= length)
		return (ms_strdup(""));
	else if (len > length - start)
		len = length;
	str = (char *)malloc(sizeof(char) * (len + 1));
	ms_add_garbage(&g_minishell.garbage, str);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
