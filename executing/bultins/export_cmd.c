#include "../../minishell.h"

int is_valid_identifier(char *name)
{
    int i;

    if (!name || name[0] == '\0')
        return 0;
    
    if (!isalpha(name[0]) && name[0] != '_')
        return 0;
    
    i = 1;
    while (name[i])
    {
        if (!isalnum(name[i]) && name[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

void print_export_vars(char **envp)
{
    char **env_ptr;
    char *equal_pos;
    char *name;
    char *value;
    int name_len;

    if (!envp)
        return;
    
    env_ptr = envp;
    while (*env_ptr)
    {
        equal_pos = strchr(*env_ptr, '=');
        if (equal_pos)
        {
            name_len = equal_pos - *env_ptr;
            name = malloc(name_len + 1);
            if (!name)
                return;
            strncpy(name, *env_ptr, name_len);
            name[name_len] = '\0';
            value = equal_pos + 1;
            
            printf("%s=\"%s\"\n", name, value);
            free(name);
        }
        else
            printf("%s\n", *env_ptr);
        env_ptr++;
    }
}

char *find_env_var(char **envp, char *name)
{
    char **env_ptr;
    char *equal_pos;
    int name_len;

    if (!envp || !name)
        return NULL;
    
    name_len = strlen(name);
    env_ptr = envp;
    
    while (*env_ptr)
    {
        equal_pos = strchr(*env_ptr, '=');
        if (equal_pos && (equal_pos - *env_ptr) == name_len 
            && strncmp(*env_ptr, name, name_len) == 0)
        {
            return equal_pos + 1;
        }
        env_ptr++;
    }
    return NULL;
}

int count_env_vars(char **envp)
{
    int count = 0;
    
    if (!envp)
        return 0;
    
    while (envp[count])
        count++;
    
    return count;
}

char **add_env_var(char **envp, char *name, char *value)
{
    char **new_envp;
    char *new_var;
    char *existing_value;
    int env_count;
    int i, j;
    int name_len;
    int value_len;

    if (!name)
        return envp;
    
    name_len = strlen(name);
    value_len = value ? strlen(value) : 0;
    env_count = count_env_vars(envp);
    existing_value = find_env_var(envp, name);
    
    new_var = malloc(name_len + value_len + 2); 
    if (!new_var)
        return envp;
    
    if (value)
        sprintf(new_var, "%s=%s", name, value);
    else
        sprintf(new_var, "%s=", name);
    
    if (existing_value)
    {
        new_envp = malloc((env_count + 1) * sizeof(char *));
        if (!new_envp)
        {
            free(new_var);
            return envp;
        }
        
        i = 0;
        j = 0;
        while (envp[i])
        {
            char *equal_pos = strchr(envp[i], '=');
            if (equal_pos && (equal_pos - envp[i]) == name_len 
                && strncmp(envp[i], name, name_len) == 0)
                new_envp[j] = new_var;
            else
            {
                new_envp[j] = ft_strdup(envp[i]);
                if (!new_envp[j])
                {
                    while (--j >= 0)
                        free(new_envp[j]);
                    free(new_envp);
                    free(new_var);
                    return envp;
                }
            }
            i++;
            j++;
        }
        new_envp[j] = NULL;
    }
    else
    {
        new_envp = malloc((env_count + 2) * sizeof(char *));
        if (!new_envp)
        {
            free(new_var);
            return envp;
        }
        i = 0;
        while (i < env_count)
        {
            new_envp[i] = ft_strdup(envp[i]);
            if (!new_envp[i])
            {
                while (--i >= 0)
                    free(new_envp[i]);
                free(new_envp);
                free(new_var);
                return envp;
            }
            i++;
        }
        
        new_envp[env_count] = new_var;
        new_envp[env_count + 1] = NULL;
    }
    
    return new_envp;
}

int parse_assignment(char *arg, char **name, char **value)
{
    char *equal_pos;
    int name_len;

    equal_pos = strchr(arg, '=');
    if (equal_pos)
    {
        name_len = equal_pos - arg;
        *name = malloc(name_len + 1);
        if (!*name)
            return -1;
        strncpy(*name, arg, name_len);
        (*name)[name_len] = '\0';
        *value = ft_strdup(equal_pos + 1);
        if (!*value)
        {
            free(*name);
            return -1;
        }
    }
    else
    {
        *name = ft_strdup(arg);
        if (!*name)
            return -1;
        *value = NULL;
    }
    return 0;
}

void free_env_array(char **envp)
{
    int i = 0;
    
    if (!envp)
        return;
    
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

int ft_export(char **av, char ***envp)
{
    int i;
    int exit_status;
    int arg_count;
    char *name;
    char *value;
    char **new_envp;

    exit_status = 0;
    arg_count = cnt_string(av);
    
    if (arg_count == 1)
    {
        print_export_vars(*envp);
        return 0;
    }
    
    i = 1;
    while (av[i])
    {
        name = NULL;
        value = NULL;
        
        if (parse_assignment(av[i], &name, &value) == -1)
        {
            printf("minishell: export: memory allocation error\n");
            exit_status = 1;
            i++;
            continue;
        }
        
        if (!is_valid_identifier(name))
        {
            printf("minishell: export: `%s': not a valid identifier\n", av[i]);
            exit_status = 1;
        }
        else
        {
            new_envp = add_env_var(*envp, name, value);
            if (new_envp != *envp)
            {
                free_env_array(*envp);
                *envp = new_envp;
            }
        }
        
        if (name)
            free(name);
        if (value)
            free(value);
        i++;
    }
    
    return exit_status;
}