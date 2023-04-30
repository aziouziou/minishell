/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:18:03 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:15 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\n')
		return (1);
	return (0);
}

int	ms_isstrspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ms_isspace(str[i++]))
			return (0);
	return (1);
}
