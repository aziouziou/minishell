/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:20:39 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:43:38 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ms_error(char *error_msg, int err_code)
{
	printf("%s.\n", error_msg);
	exit(err_code);
}

char	*ms_err_gen(char *left, char *center, char *right)
{
	char	*error_message;

	error_message = NULL;
	g_minishell.exit_status = 1;
	if (!left)
		return (NULL);
	if (center && right)
		error_message = ms_strjoin(left, ms_strjoin(center, right));
	else if (!center && right)
		error_message = ms_strjoin(left, right);
	else
		error_message = left;
	return (error_message);
}

int	ms_check_redir_error(char *buffer, int tmp_red, t_tokens *tokens)
{
	if ((!ms_strcmp(buffer, "<") || !ms_strcmp(buffer, "<<") \
	|| !ms_strcmp(buffer, ">") || !ms_strcmp(buffer, ">>")) \
	&& (tmp_red >= 3 && tmp_red <= 6))
	{
		if (tokens->next->type == 1 && tokens->next->next != NULL)
			tokens = tokens->next;
		if (tokens->next->type != 11 && tokens->next->type != 9)
			return (ms_putstr_fd(ms_err_gen(ERR_NEWLINE \
			, NULL, "\n"), 2), ERR_RET);
	}
	return (1);
}

int	ms_env_arg_error(char **command)
{
	if (!*command)
		return (1);
	while (*command)
	{
		if ((*command[0] < 'a' || *command[0] > 'z') && \
		(*command[0] < 'A' || *command[0] > 'Z'))
			return (1);
		command++;
	}
	return (0);
}

void	ms_file_descriptor_error(void)
{
	ms_putstr_fd(ms_err_gen("No such file or directory\n", NULL, NULL), 2);
}
