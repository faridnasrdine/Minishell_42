#include "../../minishell.h"

int pwd_cmd()
{
    char *path;

    path = getcwd(NULL, 0);
    if(!path)
        path = ft_strdup(getenv("PWD"));
    printf("%s\n", path);
    free(path);
    return 0;
}