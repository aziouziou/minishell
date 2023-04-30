/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:52:57 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:19 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	char	**fill_str(char **str, char const *s, char c);
static	int	count_size(char const *s, char c);
static void	free_str(char **str);

char	**ms_split(char const *s, char c)
{
	char	**str;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_size(s, c);
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	ms_add_garbage(&g_minishell.garbage, str);
	if (!fill_str(str, s, c))
	{
		free_str(str);
		return (NULL);
	}
	return (str);
}

static	char	**fill_str(char **str, char const *s, char c)
{
	int	i;
	int	temp;
	int	index;

	index = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			temp = i;
			while (s[i] != c && s[i])
				i++;
			str[index] = malloc(i - temp + 1);
			if (!str[index])
				return (NULL);
			ms_add_garbage(&g_minishell.garbage, str[index]);
			ms_strlcpy(str[index++], s + temp, i - temp + 1);
		}
	}
	str[index] = NULL;
	return (str);
}

static void	free_str(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

static	int	count_size(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}
