/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:02:07 by jsarabia          #+#    #+#             */
/*   Updated: 2023/02/21 15:37:08 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		else
			i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		n;
	int		i;
	int		j;

	j = 0;
	if (s1[0] == '\0' && s2[0] == '\0')
	{
		p = (char *)malloc(1 * sizeof(char));
		p[0] = '\0';
		return (p);
	}
	n = ft_strlen((char *)s1);
	i = ft_strlen((char *)s2);
	p = (char *)malloc((n + i) * sizeof(char) + 1);
	if (!p)
		return (NULL);
	if (s1[0] != '\0')
		ft_strlcpy(p, s1, n + 1);
	if (s2[0] != '\0')
		ft_strlcpy(p + n, s2, i + 1);
	return (p);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		while (src[i] != '\0')
			i++;
		return (i);
	}
	while ((i < n - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t n, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc(n * size);
	if (!ptr)
		return (NULL);
	while (i < (n * size))
		ptr[i++] = 0;
	return (ptr);
}
