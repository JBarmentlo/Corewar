#include <stdio.h>
#include "ft_printf.h"
#include "../libft/libft.h"

int	main(int ac, char **av)
{
	long i;
	char c;
	
	i = -12456875346576;
	(void)ac;
	(void)av;
	c = 'G';
	ft_printf("i = [%d], c = [%c], str = [%s], str = [%s]\n",i,  c, av[1], NULL);
	printf("i = [%ld], c = [%c], str = [%s], str = [%s]\n", i, c, av[1], NULL);
	return (0);
}
