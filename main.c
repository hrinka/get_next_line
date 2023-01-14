/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:14:22 by hrinka            #+#    #+#             */
/*   Updated: 2023/01/07 17:18:00 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main()
{
	char	*line;
	int		fd = open("sample.txt", O_RDONLY);

	printf("%sd\n", get_next_line(fd, &line));
	printf("%s\n", &line);
	printf("%sd\n", get_next_line(fd, &line));
	printf("%s\n", &line);
	printf("%sd\n", get_next_line(fd, &line));
	printf("%s\n", &line);
	close(fd);
}
