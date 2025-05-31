#include "../../minishell.h"

int unset_cmd(char **av)
{
    long len;

    len = cnt_string(av);
    if(len == 1)
        return 0;
    return 0;
}