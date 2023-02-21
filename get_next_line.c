/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:03:00 by jsarabia          #+#    #+#             */
/*   Updated: 2023/02/21 15:07:29 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_store(char *r)
{
	char	*store;
	char	*temp;

	if (ft_strchr(r, '\n') == NULL && r)
	{
		free(r);
		return (NULL);
	}
	temp = ft_strchr(r, '\n');
	if (!temp)
	{
		free(r);
		return (NULL);
	}
	store = ft_calloc(ft_strlen(temp), sizeof(char));
	ft_strlcpy(store, temp + 1, ft_strlen(temp));
	if (!store)
	{
		free(r);
		free (temp);
		return (NULL);
	}
	free(r);
	return (store);
}

static char	*ft_returning(char *r)
{
	int		n;
	char	*str;

	n = 0;
	if (!r)
	{
		free(r);
		return (NULL);
	}
	while (r[n] != '\0' && r[n] != '\n')
		n++;
	if (r[n] != '\0')
		n = n + 1;
	str = ft_calloc(n + 1, sizeof(char));
	ft_strlcpy(str, r, n + 1);
	if (!str || str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

static char	*ft_bufman(char *temp, char *r)
{
	char	*newbuf;

	if (temp[0] == '\0')
		return (NULL);
	else
		newbuf = ft_strjoin(r, temp);
	free(r);
	return (newbuf);
}

static char	*ft_reading(int fd, char *r)
{
	char		*buf;
	char		*temp;
	ssize_t		hola;

	if (r == NULL)
		r = (char *)ft_calloc(1, 1);
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	hola = read(fd, buf, BUFFER_SIZE);
	if (hola < 0 || ((!buf || buf[0] == '\0' || hola == 0) && !r))
	{
		free(r);
		free(buf);
		return (NULL);
	}
	temp = ft_calloc((int)hola + 1, sizeof(char));
	ft_strlcpy(temp, buf, (int)hola + 1);
	while (hola > 0)
	{
		r = ft_bufman(temp, r);
		if (ft_strchr(buf, '\n') != NULL)
			break ;
		hola = read(fd, buf, BUFFER_SIZE);
		if (hola == 0)
			break ;
		free(temp);
		temp = ft_calloc((int)hola + 1, sizeof(char));
		ft_strlcpy(temp, buf, (int)hola + 1);
	}
	free(buf);
	free(temp);
	return (r);
}

char	*get_next_line(int fd)
{
	static char	*r;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || 0 > read(fd, 0, 0))
	{
		if (r)
		{
			free(r);
			r = NULL;
		}
		return (NULL);
	}
	r = ft_reading(fd, r);
	if (r == NULL)
	{
		free(r);
		return (NULL);
	}
	str = ft_returning(r);
	r = ft_store(r);
	return (str);
}
/*
int main()
{
	char	*ptr;
	int fd;
	int n = 0;
	//system("leaks -q a.out");
	fd = open("hola.txt", O_RDONLY);
	while (n < 700)
	{
		ptr = get_next_line(fd);
		if (ptr == NULL)
			break ;
		printf("%s", ptr);
		n++;
	}
	//system("leaks -q a.out");
	return (0);
}
*/
