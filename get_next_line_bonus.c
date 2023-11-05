/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:25:27 by hrinka            #+#    #+#             */
/*   Updated: 2023/11/05 20:05:06 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*create_newline_frm_save(char *save)
{
	char	*new_line;
	size_t	i;

	if (!save || !save[0])
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, save, i + 1);
	return (new_line);
}

static char	*delete_newline_in_save(char *save)
{
	char	*new_save;
	size_t	i;
	size_t	j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\0')
		return (ft_free(&save, NULL));
	new_save = (char *)malloc(sizeof(char) * (ft_strlen_gnl(save) - i + 1));
	if (!new_save)
		return (ft_free(&save, NULL));
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	ft_free(&save, NULL);
	return (new_save);
}

static char	*read_file_and_save(int fd, char *save)
{
	char	*buf;
	ssize_t	read_bytes;
	size_t	nl_cnt;

	buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (ft_free(&save, NULL));
	read_bytes = 1;
	nl_cnt = 0;
	while (nl_cnt == 0 && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (ft_free(&buf, NULL));
		buf[read_bytes] = '\0';
		nl_cnt = cnt_chr_in_str('\n', buf);
		save = strjoin_and_free_dst(save, buf);
		if (!save)
			break ;
	}
	ft_free(&buf, NULL);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*gnl_line;
	static char	*save_buf[OPEN_MAX];

	errno = 0;
	if (fd < 0 || OPEN_MAX < fd || BUFFER_SIZE <= 0 || INT_MAX < BUFFER_SIZE)
		return (NULL);
	if (cnt_chr_in_str('\n', save_buf[fd]) == 0)
	{
		save_buf[fd] = read_file_and_save(fd, save_buf[fd]);
		if (!save_buf[fd])
			return (NULL);
	}
	gnl_line = create_newline_frm_save(save_buf[fd]);
	save_buf[fd] = delete_newline_in_save(save_buf[fd]);
	if (errno != 0)
		return (ft_free(&save_buf[fd], &gnl_line));
	return (gnl_line);
}
