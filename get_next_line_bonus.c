/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:46:13 by rumachad          #+#    #+#             */
/*   Updated: 2023/05/17 12:06:11 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*delete_line(char *nw_line)
{
	int		i;
	int		j;
	char	*left;

	if (nw_line[0] == '\0')
	{
		free(nw_line);
		return (NULL);
	}
	i = 0;
	while (nw_line[i] != '\n' && nw_line[i])
		i++;
	left = (char *)malloc((ft_strlen(nw_line) - i + 1) * sizeof(char));
	if (left == NULL)
		return (NULL);
	j = 0;
	if (nw_line[i] == '\n')
		i++;
	while (nw_line[i] != '\0')
		left[j++] = nw_line[i++];
	left[j] = '\0';
	free(nw_line);
	return (left);
}

char	*line(char *nw_line)
{
	char	*line;
	int		i;

	if (nw_line[0] == '\0')
		return (NULL);
	i = 0;
	while (nw_line[i] != '\n' && nw_line[i])
		i++;
	if (nw_line[i] == '\n')
		line = (char *)malloc(sizeof(char) * i + 2);
	else
		line = (char *)malloc(sizeof(char) * i + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (nw_line[i] != '\n' && nw_line[i])
	{
		line[i] = nw_line[i];
		i++;
	}
	if (nw_line[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*readed(char *nw_line, int fd)
{
	int		size;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	size = 1;
	while (ft_strchr(nw_line, '\n') == NULL && size != 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1)
		{
			free(nw_line);
			free(buffer);
			return (NULL);
		}
		buffer[size] = '\0';
		nw_line = ft_strjoin(nw_line, buffer);
	}
	free(buffer);
	return (nw_line);
}

char	*get_next_line(int fd)
{
	static char	*nw_line[FOPEN_MAX];
	char		*fline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	else
	{
		printf("%i\n", fd);
		nw_line[fd] = readed(nw_line[fd], fd);
		if (nw_line[fd] == NULL)
			return (NULL);
		else
		{
			fline = line(nw_line[fd]);
			nw_line[fd] = delete_line(nw_line[fd]);
			return (fline);
		}
	}
}

/* int main()
{
	int		change;
	int		i = 0;
	int		fd;
	int		fd2;
	char	*a;

	fd = open ("/nfs/homes/rumachad/42Curso/get_next_line/test.txt", O_RDWR);
	fd2 = open ("/nfs/homes/rumachad/42Curso/get_next_line/test2.txt", O_RDWR);
	change = fd;
	while (i < 9)
	{
		if (change == fd)
		{
			a = get_next_line(change);
			printf("%s", a);
			free(a);
			change = fd2;
		}
		else
		{
			a = get_next_line(change);
			printf("%s", a);
			free(a);
			change = fd;
		}
		i++;
	}
} */
