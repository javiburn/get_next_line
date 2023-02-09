#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

static int	ft_checkpos(char *str)
{
	int	n;

	n = 0;
	while (str[n] != '\0' && str[n] != '\n')
		n++;
	if (str[n] == '\n')
		return (n);
	return (-1);
}

static char	*ft_reading(int fd)
{
	static char	*buf;
	char		*ret;
	char		*end;
	ssize_t		hola;
	int			i;

	if (fd == -1)
		return (NULL);
	else
	{
		buf = (char *)malloc((BUFFER_SIZE) * sizeof(char) + 1);
		hola = read(fd, buf, BUFFER_SIZE);
		if (ft_checkpos(buf))
		{
			ret = ft_substr(buf, 0, ft_checkpos(buf));
			*buf = *(buf) - ft_checkpos(buf);
			return (ret);
		}
		else if (ft_checkpos(buf) == -1)
			ret = ft_substr(buf, 0, BUFFER_SIZE);
		while (ft_checkpos(buf) == -1)
		{
			if (i == 1)
				i = 2;
			hola = read(fd, buf, BUFFER_SIZE);
			i++;
		}
		ret = ft_strjoin(ret, buf);
		//strjoin
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	char	*str;

	str = ft_reading(fd);
	return (str);
}

int main()
{
	char	*ptr;
	int fd;
	int n = 0;

	fd = open("/Users/jsarabia/C_Cursus/get_next_line/hola.txt", O_RDONLY);
	while (n < 16)
	{
		ptr = get_next_line(fd);
		printf("%s\n", ptr);
		n++;
	}
	return (0);
}
