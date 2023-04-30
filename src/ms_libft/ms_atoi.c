/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:32:20 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:10 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ms_ispase(char c);

int	ms_atoi(const char *str)
{
	size_t	i;
	size_t	n;
	size_t	r;

	i = 0;
	n = 1;
	r = 0;
	while (ms_ispase(str[i]))
		i++;
	if (str[i] == '-')
	{
		n = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ms_isdigit(str[i]))
	{
		r *= 10;
		r += str[i] - 48;
		i++;
	}
	return (r * n);
}

static int	ms_ispase(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
