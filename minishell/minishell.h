/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:15:30 by nafarid           #+#    #+#             */
/*   Updated: 2025/08/13 11:11:20 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_gc
{
	void				*data;
	struct s_gc			*next;
}						t_gc;

typedef struct s_token
{
	char				type;
	char				*quote;
	char				*value;
	int					strip;
	int					expanded;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd_exec
{
	char				*name;
	char				meaning;
	char				*value;
	int					status;
	struct s_cmd_exec	*next;
}						t_cmd_exec;

typedef struct s_cmd
{
	int					id;
	int					builtin;
	char				**args;
	char				*op;
	char				*op_value;
	int					std_in;
	int					std_in_dup1;
	int					std_out_dup1;
	int					std_out;
	int					std_err;
	int					pipe_in;
	int					path_error;
	int					pipe_out;
	int					pipe;
	char				*path;
	char				delimiter;
	int					redir_error;
	struct s_cmd		*next;
}						t_cmd;

int						arg_count(t_token **toks, t_cmd *cmd);
int						handle_single_quotes(t_token *toks, int i);
int						handle_dollar_sign(t_token *toks, int i,
							t_cmd_exec *env_lst);
int						count_cmds(t_cmd *cmd);
int						search_and_replace(t_token *t, int *i,
							t_cmd_exec *env_lst, int w);
int						handle_double_quotes(t_token *toks, int *i,
							t_cmd_exec *env_lst);
int						len_till_expansion(char *s, int start_pos);
void					ft_quote_removal(t_token **toks);
void					toks_arr(char *line, char *chars, t_token **toks);
void					check_if_should_split(t_token *toks);
int						parsing_line(char *line, t_token **toks,
							t_cmd_exec **env_lst);
int						copy_quotes(t_token *t, t_cmd_exec *env_lst, int i,
							int j);
void					p_expansion(t_token *toks, t_cmd_exec *env_lst);
char					*erase_spaces(char *str);
t_token					*lst_new_ele_tok(char type, char *value);
void					toks_trim(t_token **toks);
t_token					*lst_last_tok(t_token *lst);
t_cmd_exec				*lst_new_ele(char *name, char *value);
void					lstadd_back_tok(t_token **lst, t_token *node);
int						tokens_count(char *line, char *chars);
int						toks_to_struct(t_token **toks, t_cmd **cmd,
							t_cmd_exec **env_lst);
int						parsing_opers(t_token **toks, t_cmd *cmd,
							t_cmd_exec **env_lst);
void					quote_del(t_token *toks);
int						get_exit_code(void);
void					set_exit_code(int code);
int						heredoc(t_cmd *cmd, t_cmd_exec **env_lst);
int						ft_cd(t_cmd *cmd, t_cmd_exec **env_lst);
int						ft_pwd(t_cmd_exec **env_lst);
int						ft_unset(t_cmd *cmd, t_cmd_exec **env_lst);
int						ft_echo(t_cmd *cmd, t_cmd_exec **env_lst);
int						ft_env(t_cmd_exec **env_lst);
int						ft_exit(t_cmd *cmd, t_cmd_exec **env_lst);
char					*check_dir(t_cmd_exec **env_lst, char *path);
int						ft_export(t_cmd *cmd, t_cmd_exec **env_lst);
int						check_var_name(char *str, int *res,
							t_cmd_exec **env_lst);
void					child_proc(t_cmd **cmd, t_cmd_exec **env_lst, int id);
char					*find_cmd(t_cmd *cmd, t_cmd_exec *env_lst);
void					exec_built(t_cmd *cmd, t_cmd_exec **env_lst,
							int child_par);
void					ft_signals(void);
void					func(t_token *t, int *j);
void					dups(t_cmd *tmp);
void					check_if_dir(t_cmd *exec_cmd);
t_cmd					*close_pipes(t_cmd **cmd, int id);
char					*getold(t_cmd_exec **env_lst);
void					change_env(char *oldpwd, char *newpwd,
							t_cmd_exec *env_lst);
int						exec_run(t_cmd *cmd, t_cmd_exec **env_lst);
void					exec_run_par(t_cmd *cmd, t_cmd_exec **env_lst);
void					check_dir_exe(t_cmd *tmp, t_cmd_exec **env_lst,
							t_cmd **cmd);
int						parent_heredoc(pid_t pid, t_cmd *cmd, int *heredoc);
void					parent_proc(t_cmd_exec **env_lst, int idx,
							int *pids);
pid_t					*allocate_pid_array(t_cmd *cmd);
void					waiting(t_cmd_exec **env_lst, int idx,
							int *pids);
void					ft_exitt(int *status);
char					*file_random(void);
void					handle_ctrl_c_heredoc(int sig);
void					ft_handle_sigint(int sig);

void					*ft_malloc(size_t size);
void					free_grabage(void);
char					*check_is_path_fail(t_cmd *cmd);
int						env_to_lst(char **env, t_cmd_exec **env_lst);
void					restore_std_fds(void);
void					change_stat(t_cmd_exec **env_lst, int stat);
void					ft_lstadd_front(t_cmd_exec **lst, t_cmd_exec *new);
void					ft_lstadd_back(t_cmd_exec **lst, t_cmd_exec *new);
t_cmd_exec				*ft_lstlast(t_cmd_exec *lst);
void					remove_empty_tokens(t_token **toks);
void					quote_count(t_token *toks);
int						handle_split(t_token *toks, char *value);
int						split_token_into_nodes(t_token *tok);
char					*ft_strjoin_sep(char *path, char *cmd, char c);
void					build_new_tok_val(t_token *toks, char *value, int i,
							int j);
char					**env_lst_to_arr(t_cmd_exec *env_lst, char meaning,
							int quote);
void					exec(t_cmd **cmd, t_cmd_exec **env_lst);

#endif