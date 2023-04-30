/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_libft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:27:54 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:43 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LIBFT_H
# define MS_LIBFT_H

# include "minishell.h"

/*	Functions	*/

char		*ms_itoa(int nb);
char		*ms_strchr(const char *s, int c);
char		*ms_strdup(const char *s);
char		*ms_strjoin(char const *s1, char const *s2);
char		*ms_strndup(char *str, int n);
char		*ms_strnstr(const char *haystack, const char *needle, size_t len);
char		*ms_strstr(char *str, char *to_find);
char		*ms_strtrim(char const *s1, char const *set);
char		*ms_substr(char const *s, unsigned int start, size_t len);
char		**ms_split(char const *s, char c);

int			ms_atoi(const char *str);
int			ms_isalnum(int c);
int			ms_isalpha(int c);
int			ms_isdigit(int c);
int			ms_isspace(char c);
int			ms_is_whitespace(char *input);
int			ms_strcmp(char *s1, char *s2);

void		ms_putstr_fd(char *s, int fd);
void		*ms_memcpy(void *dst, const void *src, size_t n);

#endif
