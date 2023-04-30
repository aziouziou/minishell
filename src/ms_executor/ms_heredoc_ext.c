/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:40:03 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:02 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_get_filename(char *filename)
{
	if (ms_check_file_exist(filename))
		return (ms_get_filename(ms_strjoin(filename, "_c")));
	return (filename);
}

int	ms_check_file_exist(char *filename)
{
	DIR				*dir;
	struct dirent	*dp;

	if (!filename)
		return (0);
	dir = opendir("/tmp");
	if (dir != NULL)
	{
		dp = readdir(dir);
		while (dp)
		{
			if (!ms_strcmp(ms_strchr(filename, '.'), dp->d_name))
				return (closedir(dir), 1);
			dp = readdir(dir);
		}
	}
	closedir(dir);
	return (0);
}
