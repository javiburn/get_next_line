/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:03:00 by jsarabia          #+#    #+#             */
/*   Updated: 2023/02/09 17:04:42 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"


static int	ft_checkpos(char *str)
{
	int 		n;

	n = 0;
	while (str[n] != '\0' && str[n] != '\n')
		n++;
	if (str[n] == '\n')
		return (n);
	return (-1);
}

static int	ft_lenspace(char *str)
{
	int	lenspace;
	int	nextspace;

	lenspace = 1;
	nextspace = ft_checkpos(str) + 1;
	while (str[nextspace] != '\n' && nextspace <= BUFFER_SIZE)
	{
		nextspace++;
		lenspace++;
	}
	return (lenspace);
}

static char	*ft_create(char *str)
{
	static char	start[BUFFER_SIZE];
	char		*ret;

	ret = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	ret = ft_strjoin(start, (char const *)str);
	if (!ret)
		return (NULL);
	ft_strlcpy(start, str + ft_checkpos(str), BUFFER_SIZE - ft_checkpos(str) + 1);
	return (ret);
}

static char	*ft_reading(int fd)
{
	static char	*buf;
	char		*toret;
	ssize_t		hello;

	if (fd == -1)
		return (NULL);
	else
	{
		buf = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
		hello = read(fd, buf, BUFFER_SIZE);
		if (hello == 0)
			return (NULL);
	}
	toret = ft_strdup((const char *)(buf));
	return (toret);
}

char	*get_next_line(int fd)
{
	char		*temp;
	char		*temp2;
	char		*str;
	static int	check = 0;
	static int	antlen = 0;

	temp = ft_strdup(ft_reading(fd));
	if (!temp)
		return (NULL);
	if (ft_checkpos(temp) != -1)
	{
		str = malloc((antlen + ft_checkpos(temp)) * sizeof(char) + 1);
		ft_strlcpy(str, ft_create(temp), antlen + ft_checkpos(temp) + 1);
		antlen = ft_lenspace(temp);
		free(temp);
		return (str);
	}
	ft_strlcpy(str, temp, BUFFER_SIZE + 1);
	while (ft_checkpos(temp) == -1)
	{
		free(temp2);
		temp2 = malloc(BUFFER_SIZE * sizeof(char) + 1);
		temp2 = ft_strdup(ft_reading(fd));
		ft_strlcpy(str, temp2, BUFFER_SIZE);
	}
	//WIT: -queda hacer que se almacene la longitud del string temp
	//     -queda por poner lo que pasa si no hay \n (que vuelva al bucle)
	return (str);
}

int main()
{
	char	*ptr;
	int fd;
	int n = 0;
	system("leaks -q a.out");
	fd = open("/Users/jsarabia/C_Cursus/get_next_line/hola.txt", O_RDONLY);
	while (n < 7)
	{
		ptr = get_next_line(fd);
		printf("%s\n", ptr);
		n++;
	}
	system("leaks -q a.out");
	return (0);
}
