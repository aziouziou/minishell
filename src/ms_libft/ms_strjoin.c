/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:48:53 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:23 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ms_strlen(s1);
	s2_len = ms_strlen(s2);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	ms_add_garbage(&g_minishell.garbage, str);
	if (!str)
		return (NULL);
	ms_memcpy(str, s1, s1_len);
	ms_memcpy(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}
