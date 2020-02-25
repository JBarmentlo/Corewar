#include "op.h"
#include "jasm.h"
#include "stdio.h"
#include "unistd.h"

int	main(int ac, char **av)
{
	header_t header;

	is_file_ok(av[1]);
	ac++;

}