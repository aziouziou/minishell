/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:39:31 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:17 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_size(long long n);

char	*ms_itoa(int nb)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = count_size(nb);
	i = 0;
	if (nb < 0 || len == 0)
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, str);
	str[len] = '\0';
	if (nb < 0)
	{
		nb *= -1;
		str[i++] = '-';
	}
	while (len-- > i)
	{
		str[len] = (nb % 10) + 48;
		nb /= 10;
	}
	return (str);
}

static int	count_size(long long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
