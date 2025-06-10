#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <termios.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef enum s_token_type
{
	T_IDENTIFIER, /*thsi is cmd or file name*/
	T_PIPE,		  /*this is pipe ->> '|'*/
	T_AND,		  /*this is and --> ' && '*/
	T_OR,		  /*this is or --> ' || '*/
	// T_O_PARENT, /*this is open Parenthesis --> ' ( ' */
	// T_C_PARENT, /*this is close Parenthesis --> ' ) '*/
	T_DGREAT, /*this is  double greater than --> ' >> '*/
	T_GREAT,  /*this is greater than --> ' > '*/
	T_DLESS,  /*this is double less than --> ' << ' */
	T_LESS,	  /*this is less than-->  ' < ' */
} t_token_type;

typedef struct s_qout
{
	int i;
	int in_quote;
	char quote_char;
	char *result;
	char *tmp;
} t_qout;
typedef struct s_cmd
{
	char *cmd;
	char *token;

} t_cmd;

typedef struct s_dolar
{
	int i;
	char *result;
	char *tmp;
	char *var_name;
	char *var_value;
	int in_single_quote;
	int in_double_quote;
	int start;
} t_dolar;

typedef struct s_list
{
	char *content;
	t_token_type type;
	struct s_list *next;
} t_list;
// =======Command to Execute Structure ========
typedef struct s_cmd_exec
{
	char **argv; // arguments for the command
	char *path;
	int hd_fd;
} t_cmd_exec;

typedef struct s_data
{
	t_cmd_exec *cmd_exec; // array of commands to execute
	t_list *cdm_list;	  // linkd list of token
	char **envp;
	int og_fd[2]; // original stdin/out (to restore after redirections)
	int exit_status;

} t_data;

t_list *paring_cmd(char *cmd);
int is_meta(char str);
int ft_lstadd_back(t_list **lst, t_list *new);
int ft_lstsize(t_list *lst);
char *checking_dolar(char *str);
char *ft_strjoin_free(char *s1, char *s2);
char *skip_qouts(char *str);
t_list *fill_node(char *content, t_token_type t_type);
int checking_close_qoutes(char *str);
int checking_cmd(t_list **list);
t_cmd_exec *create_cmd_exec(t_list *cmd_list);
void ft_strncpy(char *dest, const char *src, int n);
void ft_strcpy(char *dest, const char *src);
void ft_strcat(char *dest, const char *src);
int ft_strncmp(const char *str1, const char *str2, int n);
///////////////////////////////////////////////===>free
void ft_lstclear(t_list **lst);
void free_string(char **str);
void clear_data(t_data *data);

//////////////////////////////////////////////////////===>test
const char *token_type_to_string(t_token_type type);
//////////////////////////////////////////////////////////
int execute_builtin(t_cmd_exec *cmd, t_data *data);
int signal_exec(t_data *data);
int cnt_string(char **str);
int execute_command(t_data *data);
//////////////////////////////////////////////////===>BUILTIN
int	cd_cmd(char **av);
int pwd_cmd();
int exit_cmd(char **av);
int unset_cmd(char **av);
int print_echo(char **av);
int export_cmd(char **av, char ***envp);
int env_cmd(char **av, char **envp);
#endif