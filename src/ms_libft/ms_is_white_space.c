/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_white_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:10:42 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:11 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_is_whitespace(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == 32 || input[i] == '\t' || (input[i] >= 9 && input[i] \
			<= 15))
			j++;
		i++;
	}
	if (j == i)
		return (0);
	return (1);
}
