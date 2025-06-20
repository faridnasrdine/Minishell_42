/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:51:29 by nafarid           #+#    #+#             */
/*   Updated: 2025/06/19 15:34:35 by nafarid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
void print_export(char **envp)
{
	char **env;
	char *pos;
	char *befor;
	char *after;
	int i;
	int len;

	i = 0;
	env = envp;
	if (!envp)
		return;
	while (env[i])
	{
		pos = ft_strchr(env[i], '=');
		if (pos)
		{
			len = pos - env[i];
			befor = malloc((len + 1) * sizeof(char));
			if (!befor)
				return;
			ft_strncpy(befor, env[i], len);
			befor[len] = '\0';
			after = pos + 1;
			printf("declare -x %s=\"%s\"\n", befor, after);
			free(befor);
		}
		else
			printf("declare -x %s\n", env[i]);
		i++;
	}
}
int new_var(char *str, char **new, char **val)
{
	int len;
	char *pos;

	pos = ft_strchr(str, '=');
	if (pos)
	{
		len = pos - str;
		*new = malloc(sizeof(char) * (len + 1));
		if (!*new)
			return 1;
		ft_strncpy(*new, str, len);
		(*new)[len] = '\0';
		*val = ft_strdup(pos + 1);
		if (!*val)
		{
			free(*new);
			return 1;
		}
	}
	else
	{
		*new = ft_strdup(str);
		if (!*new)
			return 1;
		*val = NULL;
	}
	return 0;
}
int valid_identifier(char *str)
{
	int i;

	if (!str || str[0] == '\0')
		return 1;
	if (str[0] == '-' && ft_isalpha(str[1]))
		return 2;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return 1;
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return 1;
		i++;
	}
	return 0;
}

int find_var(char **envp, char *new)
{
	char **env;
	int len;
	char *pos;
	int i;

	i = 0;
	len = ft_strlen(new);
	env = envp;
	while (env[i])
	{
		pos = ft_strchr(env[i], '=');
		if (pos && ((pos - env[i]) == len) && (strncmp(env[i], new, len) == 0))
			return i;
		if (!pos && (strcmp(env[i], new) == 0))
			return i;
		i++;
	}
	return -1;
}
typedef struct s_env
{
	int len_new;
	int len_val;
} t_env;

char *create_new_var(char *new, char *val)
{
	char *new_var;
	int len_new;
	int len_val;

	len_new = ft_strlen(new);
	len_val = 0;
	if (val)
		len_val = ft_strlen(val);
	if (val)
	{
		new_var = malloc((len_new + len_val + 2) * (sizeof(char)));
		if (!new_var)
			return NULL;
		ft_strcpy(new_var, new);
		ft_strcat(new_var, "=");
		ft_strcat(new_var, val);
	}
	else
	{
		new_var = malloc((len_new + 1) * (sizeof(char)));
		if (!new_var)
			return NULL;
		ft_strcpy(new_var, new);
	}
	return new_var;
}
char **replace_var(char **envp, int index, int len_env, char *new_var)
{
	char **new_envp;
	int i;
	int j;

	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * (len_env + 1));
	if (!new_envp)
		return NULL;
	while (envp[i])
	{
		if (i == index)
			new_envp[j] = new_var;
		else
		{
			new_envp[j] = ft_strdup(envp[i]);
			if (!new_envp[j])
			{
				free_string(new_envp, new_var);
				return envp;
			}
		}
		i++;
		j++;
	}
	new_envp[j] = NULL;
	return new_envp;
}

char **create_new_env(char **envp, char *new_var, int len_env)
{
	char **new_envp;
	int i;
	
	new_envp = malloc(sizeof(char *) * (len_env + 2));
	if (!new_envp)
	{
		free(new_var);
		return envp;
	}
	i = 0;
	while (i < len_env)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			free_string(new_envp, new_var);
			return envp;
		}
		i++;
	}
	new_envp[len_env] = new_var;
	new_envp[len_env + 1] = NULL;
	return new_envp;
}
char **add_new_var(char **envp, char *new, char *val)
{
	char *new_var;
	char **new_envp;
	int index;
	int len_env;

	len_env = cnt_string(envp);
	index = find_var(envp, new);
	if (!new)
		return envp;
	new_var = create_new_var(new, val);
	if (!new_var)
		return envp;
	if (index >= 0)
	{
		new_envp = replace_var(envp, index, len_env, new_var);
		if(!new_envp)
		{
			free_string(new_envp, new_var);
			return envp;
		}
	}
	else
		new_envp = create_new_env(envp, new_var, len_env);
	return new_envp;
}

int export_cmd(char **av, char ***envp)
{
	int len;
	int i;
	int exit_status;
	char *new;
	char *val;
	char **new_envp;

	i = 1;
	exit_status = 0;
	len = cnt_string(av);
	if (len == 1)
		print_export(*envp);
	while (av[i])
	{
		if (new_var(av[i], &new, &val) == 1)
		{
			printf("minishell: export: memory allocation error\n");
			exit_status = 1;
		}
		if (valid_identifier(new) == 1)
		{
			printf("Minishell: export: '%s': not a valid identifier\n", new);
			exit_status = 1;
		}
		else if (valid_identifier(av[i]) == 2)
		{
			printf("Minishell: export: %c%c: invalid option\n", new[0], new[1]);
			exit_status = 1;
		}
		else
		{
			new_envp = add_new_var(*envp, new, val);
			if (new_envp != *envp)
			{
				free_string(*envp, NULL);
				*envp = new_envp;
			}
		}
		if (new)
			free(new);
		if (val)
			free(val);
		i++;
	}
	return exit_status;
}
