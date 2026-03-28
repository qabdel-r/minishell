/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/17 15:45:33 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# define _BSD_SOURCE

# include <sys/types.h>
# include <stdlib.h>
# include <stddef.h>
# include <signal.h>

extern volatile sig_atomic_t	g_sig;

typedef enum e_qtype
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_qtype;

typedef enum e_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_IN,
	TOK_OUT,
	TOK_APPEND,
	TOK_HEREDOC
}	t_toktype;

typedef struct s_part
{
	char			*text;
	t_qtype			qtype;
	struct s_part	*next;
}	t_part;

typedef struct s_token
{
	t_toktype		type;
	t_part			*parts;
	struct s_token	*next;
}	t_token;

typedef struct s_arg
{
	t_part			*parts;
	struct s_arg	*next;
}	t_arg;

typedef struct s_redir
{
	t_toktype		type;
	t_part			*target_parts;
	int				heredoc_expand;
	int				hd_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_arg			*args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd			*cmds;
	int				count;
}	t_pipeline;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	int		last_status;
	int		tty_fd;
	pid_t	pgid;
	int		should_exit;
	int		exit_status;
}	t_shell;

t_token		*ms_lex_line(const char *line, int *err);
int			ms_validate_tokens(t_token *tokens, int *err);
int			ms_parse_line(const char *line, t_pipeline **out);
int			ms_parse_tokens(t_token **tokens, t_pipeline **out, int *err);
int			ms_tok_is_redir(t_toktype t);
int			ms_parts_has_quote(t_part *p);
void		ms_debug_pipeline(t_pipeline *p);

void		ms_setup_signals(void);
void		ms_hd_setup_signals(void);
void		ms_exec_setup_signals(void);

void		ms_shell_loop(t_shell *sh);
void		ms_jobctl_init(t_shell *sh);
void		ms_jobctl_cleanup(t_shell *sh);
void		ms_jobctl_set_fg(t_shell *sh, pid_t pgid);

t_env		*ms_env_from_envp(char **envp);
void		ms_env_clear(t_env **env);
char		*ms_env_get(t_env *env, const char *key);
int			ms_env_set(t_env **env, const char *k, const char *v, int ovr);
int			ms_env_unset(t_env **env, const char *key);
t_env		*ms_env__new_and_add(t_env **env, char *k, char *v);

int			ms_execute(t_shell *sh, t_pipeline *p);

int			ms_is_builtin(const char *name);
int			ms_run_builtin(t_shell *sh, char **argv);
int			ms_builtin_echo(char **argv);
int			ms_builtin_pwd(void);
int			ms_builtin_env(t_shell *sh);
int			ms_builtin_cd(t_shell *sh, char **argv);
int			ms_builtin_export(t_shell *sh, char **argv);
int			ms_builtin_unset(t_shell *sh, char **argv);
int			ms_builtin_exit(t_shell *sh, char **argv);

void		ms_putstr_fd(const char *s, int fd);
void		ms_putendl_fd(const char *s, int fd);
const char	*ms_tok_repr(t_toktype type);
void		ms_syntax_error(const char *tok);

char		**ms_args_to_argv(t_arg *args);
void		ms_argv_free(char **argv);
char		**ms_args_to_argv_expanded(t_shell *sh, t_arg *args);

char		*ms_parts_join(t_part *parts);
char		*ms_expand_parts(t_shell *sh, t_part *parts);
char		*ms_expand_str(t_shell *sh, const char *s);

t_part		*ms_part_new(char *text, t_qtype qtype);
void		ms_part_add_back(t_part **lst, t_part *new_node);
void		ms_part_clear(t_part **lst);

t_token		*ms_token_new(t_toktype type, t_part *parts);
void		ms_token_add_back(t_token **lst, t_token *new_node);
void		ms_token_clear(t_token **lst);

t_arg		*ms_arg_new(t_part *parts);
void		ms_arg_add_back(t_arg **lst, t_arg *new_node);
void		ms_arg_clear(t_arg **lst);

t_redir		*ms_redir_new(t_toktype type, t_part *target, int h_expand);
void		ms_redir_add_back(t_redir **lst, t_redir *new_node);
void		ms_redir_clear(t_redir **lst);

t_cmd		*ms_cmd_new(void);
void		ms_cmd_clear(t_cmd **lst);

t_pipeline	*ms_pipeline_new(void);
void		ms_pipeline_clear(t_pipeline **p);

int			ms_is_space(char c);
int			ms_is_op(char c);
size_t		ms_strlen(const char *s);
char		*ms_strndup(const char *s, size_t n);
char		*ms_strdup(const char *s);
int			ms_strcmp(const char *a, const char *b);
int			ms_strncmp(const char *a, const char *b, size_t n);
char		*ms_strchr(const char *s, int c);
char		*ms_strjoin(const char *a, const char *b);
char		*ms_strjoin3(const char *a, const char *b, const char *c);

char		**ms_env_to_envp(t_env *env);
void		ms_envp_free(char **envp);

char		*ms_resolve_cmd(t_shell *sh, const char *name, int *st);
int			ms_exec_external(t_shell *sh, char **argv);
int			ms_exec_pipeline(t_shell *sh, t_pipeline *p);
void		ms_exec_external_in_child(t_shell *sh, char **argv);
int			ms_exec_external_cmd(t_shell *sh, t_cmd *cmd, char **argv);

int			ms_redirs_setup_child(t_cmd *cmd);
int			ms_redirs_setup_parent(t_cmd *cmd, int *save_in, int *save_out);
void		ms_redirs_restore_parent(int save_in, int save_out);

int			ms_prepare_heredocs(t_shell *sh, t_pipeline *p);
void		ms_cleanup_heredocs(t_pipeline *p);

#endif
