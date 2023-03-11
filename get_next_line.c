/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:19:18 by hrinka            #+#    #+#             */
/*   Updated: 2023/03/11 19:45:00 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_helper(char *save, char *buf)
{
	free(save);
	save = NULL;
	free(buf);
	buf = NULL;
	return (NULL);
}

char	*ft_read(int fd, char *save)
{
	char	*buf;
	int		read_byte;
	char	*tmp;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_byte = 1;
	while (!ft_strchr(save, '\n') && read_byte != 0)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte < 0)
			return (free_helper(save, buf));
		buf[read_byte] = '\0';
		tmp = ft_strjoin(save, buf);
		if (tmp == NULL)
			return (free_helper(save, buf));
		free(save);
		save = tmp;
	}
	free (buf);
	return (save);
}

char	*ft_get_line(char *save)
{
	size_t	i;
	char	*s;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		s[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		s[i] = save[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_save(char *save)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!s)
	{
		free (save);
		return (NULL);
	}
	i += 1;
	c = 0;
	while (save[i])
		s[c++] = save[i++];
	s[c] = '\0';
	free (save);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	if (line == NULL)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = ft_save(save);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("./gnlTester/files/empty", O_RDONLY);
// 	get_next_line(fd);
// 	get_next_line(fd);
// }
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("> %s", line);
// 		free(line);
// 	}
// 	close (fd);
// 	return (0);
// }

// __attribute__((destructor))
// static void	destructor(void) {
// 	system("leaks -q a.out");
// }
