#include "op.h"
#include "jasm.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct	s_cor
{
	header_t	header;

}				t_cor;



int	main(int ac, char **av)
{
	struct stat ss;
	int			fd;
	char		*text;

	is_file_ok(av[1]);
	fd = open(av[1], O_RDONLY);
	fstat(fd, &ss);
	printf("size: %lld\n", ss.st_size);
	text = malloc(ss.st_size + 1);
	read(fd, text, ss.st_size);
	ac++;
	printf("%s", text);

}