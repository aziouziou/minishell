/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:30:16 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:25 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_strndup(char *str, int n)
{
	char	*tmp;
	int		i;
	int		str_len;

	i = 0;
	str_len = ms_strlen(str);
	tmp = malloc(sizeof(char) * (str_len + 1));
	if (!tmp)
		return (NULL);
	while (str[i] && i < n)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
