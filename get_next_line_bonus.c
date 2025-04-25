/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:25:21 by beatde-a          #+#    #+#             */
/*   Updated: 2025/04/16 14:25:27 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

char	*read_file(int fd, char *buffer)
{
	char		*line;
	ssize_t		bytes_read;

	line = NULL;
	while (1)
	{
		if (!buffer[0])
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
			{
				if (bytes_read < 0)
					clear_line(&line);
				return (line);
			}
			buffer[bytes_read] = '\0';
		}
		extract_line(buffer, &line);
		reset_buffer(buffer);
		if (line && line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(BUFFER_SIZE + 1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	return (read_file(fd, buffer[fd]));
}

/*void	run_test(int fd)
{
	char	*line;
	
	line = get_next_line(fd);
	if (line)
	{
		printf("%s\n", line);
		free(line);
	}
}

int	main(void)
{
	int	fd[4];
	int	i;

	fd[0] = open("data/test0.txt", O_RDONLY);
	fd[1] = open("data/test1.txt", O_RDONLY);
	fd[2] = open("data/test2.txt", O_RDONLY);
	fd[3] = open("data/test4.txt", O_RDONLY);
			
	i = 0;
	while (i < 3)
	{
		run_test(fd[0]);
		run_test(fd[1]);
		run_test(fd[2]);
		run_test(fd[3]);
		i++;
	}

	i = 0;
	while (i < 4)
	{
		close(fd[i]);
		i++;
	}

	return (0);
}*/

/*TEST
BUFFER_SIZE = 42
BUFFER_SIZE = 1
BUFFER_SIZE = 10
BUFFER_SIZE = 9999
BUFFER_SIZE = 0
BUFFER_SIZE = -1
without -D flag
*/