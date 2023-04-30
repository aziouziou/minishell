/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:13:35 by abziouzi          #+#    #+#             */
/*   Updated: 2023/01/12 01:42:40 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes - Standard libraries */

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* Includes - Custom libraries */

# include "ms_libft.h"

/*	Definitions	*/

# define PROMPT			"> minishell-$ "
# define STD_PATH		"/usr/bin:/bin:/usr/sbin:/sbin:"
# define SPECIAL_CHARS	" \n\t\'\"\\+-*/^`=()[]|!?<>$@.:,;~"

# define WHITESPACE		1
# define PIPE			2	//	|
# define REDIR_IN		3	//	<
# define REDIR_OUT		4	//	>
# define APPEND			5	//	>>
# define HEREDOC		6	//	<<
# define DOLLAR			9	//	$
# define EXIT_STATUS	10	//	$?
# define WORD			11

# define RET_SUCCESS	200
# define ERR_RET		365

# define ERR_ARG		"[minishell] does not take any arguments"
# define ERR_EXP		"minshell: export: "
# define ERR_TOKEN		"minishell: syntax error, near unexpected token "
# define ERR_MALLOC		"malloc failed for [./minishell]"
# define ERR_NEWLINE	"minishell: syntax error near unexpected token		\
				newline"
# define ERR_FILE_DIR	"cd: error retrieving current directory: getcwd:	\
				cannot access parent directories: No such file or directory\n"
# define ERR_ID	"': not a valid identifier\n"

/*	Structs	*/

typedef struct s_garbage
{
	void				*garbage_ptr;

	struct s_garbage	*next;

}	t_garbage;

typedef struct s_env
{
	char			*key;
	char			*value;

	struct s_env	*next;

}	t_env;

typedef struct s_tokens
{
	char				*content;

	int					type;

	struct s_tokens		*next;

}	t_tokens;

typedef struct s_redir
{
	char			*filename;

	int				type;

	struct s_redir	*next;

}	t_redir;

typedef struct s_cmd
{
	char			**args;

	int				r_in;
	int				w_out;

	struct s_cmd	*next;

	t_redir			*redir;

}	t_cmd;

typedef struct s_minishell
{
	int			exit_status;
	int			shell_level;
	int			dup_in;
	int			dup_out;
	int			fdd;
	int			fd[2];
	int			n_h;
	int			s_h;
	int			r_in;
	int			w_out;

	t_env		*env;

	t_garbage	*garbage;

}	t_minishell;

/*	Minishell Functions*/

char		*ms_check_double_quote(t_tokens **tokens, char *input, char quote);
char		*ms_check_env(t_tokens **tokens, char *input);
char		*ms_check_redir(t_tokens **tokens, char *input);
char		*ms_check_pipe(t_tokens **tokens, char *input);
char		*ms_check_single_quote(t_tokens **tokens, char *input, char quote);
char		*ms_check_whitespace(t_tokens **tokens, char *input);
char		*ms_check_word(t_tokens **tokens, char *input, char *special_chars);
char		*ms_err_gen(char *left, char *center, char *right);
char		*ms_get_filename(char *filename);
char		*ms_get_path(void);
char		*ms_get_var(char *arg);
char		*ms_getcwd(void);
char		*ms_heredoc_ext(t_tokens *tokens);
char		*ms_in_double_quotes(t_tokens **tokens, char *input, \
			char quote, int i);
char		*ms_in_single_quotes(t_tokens **tokens, char *input, \
			char quote, int i);
char		*ms_prompt_return(char *input);
char		*ms_readline(void);
char		*ms_return_val(char *value);
char		**ms_export_env(t_env *env);

int			check_redirecrt(t_redir *redir, int *status);
int			ms_add_dollar_sign(t_tokens **tokens, char input);
int			ms_check_append(char *command);
int			ms_check_builtin(char *command);
int			ms_check_file_exist(char *filename);
int			ms_check_first_command(char *str, int status);
int			ms_check_folder(char *name);
int			ms_check_inside_env(char *arg);
int			ms_check_one_command(t_cmd *commands, t_tokens *tokens, \
			int *status);
int			ms_check_pid(int pid);
int			ms_check_pipe_is_last(t_tokens *tokens);
int			ms_check_redir_error(char *buffer, int tmp_red, t_tokens *tokens);
int			ms_check_syntax(t_tokens *tokens);
int			ms_check_valid_num(char *str, char *cmd);
int			ms_check_valid_var(char *arg, int is_equal);
int			ms_check_redirection(int type, char *filename, int *status);
int			ms_echo(char **command);
int			ms_env_arg_error(char **command);
int			ms_env_size(void);
int			ms_execve(char *path, char **command);
int			ms_export_new_arg(char **cmd, int is_append, char *var, char *val);
int			ms_is_number(char n);
int			ms_is_pipe(t_tokens *tokens);
int			ms_lexer(t_tokens **tokens, char *input);
int			ms_open_heredoc(char **value, int *type);
int			ms_open_heredoc_file(char *filename, int *status);
int			ms_open_in(char *filename, int *status);
int			ms_pipe_status(t_tokens *tokens);
int			ms_print_command(char **command);
int			ms_redir_check(t_tokens *tokens);
int			ms_redir_count(t_redir *redir);
int			ms_system_cmd(t_cmd *commands);

size_t		ms_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ms_strlen(const char *str);

t_cmd		*ms_add_new_command(char **arg, t_redir *redir);
t_cmd		*ms_free_commands(t_cmd **commands);
t_cmd		*ms_parser(t_tokens *tokens);

t_env		*ms_new_env_line(char *key, char *value);
t_env		*ms_env_line_remove(char **cmd, t_env *list);
t_env		*ms_unset(char **cmd);

t_redir		*ms_create_new_redir(int type, char *val);

t_tokens	*ms_free_tokens(t_tokens **tokens);
t_tokens	*ms_new_token(int type, char *content);

void		ms_add_command(t_cmd **commands, t_tokens *tokens);
void		ms_add_command_back(t_cmd **commands, char **arg, t_redir *redir);
void		ms_add_env_line(t_env **env, char *key, char *value);
void		ms_add_garbage(t_garbage **garbage, void *garbage_ptr);
void		ms_add_new_redir(t_redir **redir, char *value, int type);
void		ms_add_pwd_env(int status_pwd, int status_old, char *last_cmd);
void		ms_add_quotes(t_tokens **tokens, char *buffer, char quote);
void		ms_add_redir(t_redir **redir, t_tokens *tokens);
void		ms_add_token(t_tokens **tokens, char *content, int type);
void		ms_builtin(char **command, int *status);
void		ms_builtin_env(char **command);
void		ms_cd(char **command);
void		ms_cd_plus(char *cmd, char *path);
void		ms_change_pwd(char *last_cmd);
void		ms_check_exit_status(char *command);
void		ms_check_file_status(int status);
void		ms_check_heredoc(t_tokens **tokens);
void		ms_check_if_redir(t_redir *commands, int *status);
void		ms_check_newline(char **str, int status, int j);
void		ms_child_heredoc(char ***value, int *type);
void		ms_child_process(t_cmd *commands, int *status);
void		ms_error(char *error_msg, int err_code);
void		ms_executor(t_cmd *commands, t_tokens *tokens);
void		ms_exit(char **command);
void		ms_expander(t_tokens **tokens);
void		ms_expand_dollar(char **command_value, int i);
void		ms_expand_status(char **command_value);
void		ms_export(char **command);
void		ms_file_descriptor_error(void);
void		ms_free_garbage(t_garbage *garbage);
void		ms_get_export(void);
void		ms_handle(int c);
void		ms_init_env(char *envp[]);
void		ms_launch(t_tokens **tokens, t_cmd **commands, char *input);
void		ms_new_pwd_env_back(t_env **env, char *key, char *value);
void		ms_open_append(char *filename);
void		ms_open_redir_out(char *filename, int *status);
void		ms_pipe_commands(t_cmd *commands, int statuss);
void		ms_print_export(char **str);
void		ms_print_exported(char **export);
void		ms_print_tokens(t_tokens **tokens);
void		ms_pwd(void);
void		ms_run(char *envp[]);
void		ms_shell_level(char *envp[]);
void		ms_signals(void);
void		ms_signal_handler(int sig);
void		ms_signal_handler_2(int *statuss);
void		ms_switch_cd(void);
void		ms_switcher(void);
void		ms_update(char *val, char ***value);
void		ms_update_env_var(char *var, char *val, int is_append);
void		ms_wipe(t_tokens **tokens, t_cmd **commands, char *input);

extern t_minishell	g_minishell;

#endif
