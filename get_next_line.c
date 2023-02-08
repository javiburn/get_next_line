#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"


/*
char *temp(int fd)
{
	char *temp;
	char	*new;

	temp = r(fd);
	while (
}
*/
char *r(int fd)
{
	static char	*ptr;
	char		*temp;
	ssize_t		hola;
	int			i;

	i = 0;
	if (fd == -1)
		return (NULL);
	else
	{
		ptr = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
		hola = read(fd, ptr, BUFFER_SIZE);
	}
	while (ptr[i] != '\n' && i < BUFFER_SIZE)
		i++;
	if (ptr[i] == '\n')
	{
		temp = ft_substr(ptr, 0, i);
		return (temp);
	}
	else
		r(fd);
	return (NULL);
}

int main()
{
	char	*ptr;
	int fd;

	fd = open("/Users/jsarabia/C_Cursus/get_next_line/hola.txt", O_RDONLY);
	ptr = r(fd);
	printf("%s", ptr);
	return (0);
}
