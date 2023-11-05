/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:26:17 by hrinka            #+#    #+#             */
/*   Updated: 2023/11/05 18:51:29 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*strjoin_and_free_dst(char *dst, char *src);

void	*ft_free(char **alloc1, char **alloc2);

size_t	ft_strlen_gnl(const char *str);
size_t	cnt_chr_in_str(const char c, const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
