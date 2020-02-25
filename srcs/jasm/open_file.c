#include "op.h"
#include "unistd.h"
#include "libc.h"

int		file_exists(char *filename)
{
	return (access(filename, R_OK));
}

int		is_filename_ok(char *filename)
{
	int	len;

	len = strlen(filename);
	if (len < 3)
		return (0);
	if (filename[len - 1] != 's')
		return (0);
	if (filename[len - 2] != '.')
		return (0);
	if (filename[len - 3] == '/')
		return (0);
	return (1);
}

int		is_file_ok(char *filename)
{
	if (file_exists(filename) == -1)
	{
		printf("File does not exist or we do not have read permission.\n");
		return (0);
	}
	if (!is_filename_ok(filename))
	{
		printf("filename incorrect.\n");
		return (0);
	}
	return (1);
}