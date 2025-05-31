#include "../../minishell.h"

int is_valid(char *av)
{
	int i;
	int f;

	i = 0;
	if(!av || av[0] == '\0')
		return 0;
	if(av[0] == '-')
	{
		f = 1;
		i++;
	}
	if(av[0] == '+')
		i++;
	while(av[i])
	{
		if(!ft_isdigit(av[i]))
			return 1;
		i++;
	}
	return 0;
}

int exit_cmd(char **av)
{
	int len;
	long i;
	printf("exit\n");
	len = cnt_string(av);
	if (len == 1)
	{
		exit(0);
	}
	if (len == 2)
	{
		if (is_valid(av[1]) == 1)
		{
			printf("bash: exit: %s: numeric argument required\n", av[1]);
			exit(2);
		}
		i = ft_atoi(av[1]);
		i = (i % 256 + 256) % 256;
		exit(i);
	}
	return 0;
}
