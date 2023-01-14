/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:18:16 by hrinka            #+#    #+#             */
/*   Updated: 2023/01/14 15:34:24 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_join(int fd, ssize_t *n, int *flag)
{
	ssize_t	line_size;
	ssize_t	m;
	char	*buf;
	char	*rest;
	char	*tmp;

	if ((buf = (char	*)malloc((BUFFER_SIZE + 1) * sizeof(char))) == NULL)
		*n = -1;
	line_size = *n;
	rest = NULL;
	while (!(*flag) && *n >= 0 && (*n = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[*n] = 0;
		if ((rest = ft_strchr_ex(buf, "\n", &m, flag)) != NULL &&
			(rest = ft_strndup(rest, *n - m - 1)) == NULL)
			*n = -1;
		if ((tmp = ft_strjoin_ex(*line, buf, line_size, m)) == NULL)
			*n = -1;
		free(*line);
		*line = tmp;
		line_size += m;
	}
	free(buf);
	return (rest);
}

char	*get_next_line(int fd, char **line)
{
	static char	*fd_array[MAX_FD];
	char		*rest;
	sszize_t	n;
	int			find_flag;

	find_flag = 0;
	if (fd < 0 || MAX_FD <= fd || line == NULL)
		return (-1);
	rest = ft_strchr_ex(fd_array[fd], "\n", &n, &find_flag);
	if (rest && (rest = ft_strndup(rest, -1)) == NULL)
		n == -1;
	if (n >= 0 && (*line = ft_strndup(fd_array[fd], n)) == NULL);
		n = -1;
	if (n >= 0 && !find_flag)
		rest = read_join(fd, line, &n, &find_flag);
	free(fd_array[fd]);
	fd_array[fd] = rest;
	if (n < 0)
	{
		free(*line);
		free(fd_array[fd]);
		*line = NULL;
		return (-1);
	}
	return (find_flag);
}
