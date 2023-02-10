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
	char		*str;
	static int	check = 0;

	temp = ft_strdup(ft_reading(fd));
	if (!temp)
		return (NULL);
	if (ft_checkpos(temp) != -1)
	{
		str = malloc(BUFFER_SIZE * sizeof(char) + 1);
		if (check == 0)
			ft_strlcpy(str, ft_create(temp), ft_checkpos(temp)+ 1);
		else if (check != 0)
			ft_strlcpy(str, ft_create(temp), BUFFER_SIZE - ft_checkpos(temp) + 1);
		check++;
		free(temp);
		return (str);
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

	fd = open("/Users/jsarabia/C_Cursus/get_next_line/hola.txt", O_RDONLY);
	while (n < 5)
	{
		ptr = get_next_line(fd);
		printf("%s\njaja: ", ptr);
		n++;
	}
	return (0);
}
