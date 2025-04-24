/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:25:21 by beatde-a          #+#    #+#             */
/*   Updated: 2025/04/16 14:25:27 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
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
		if (line && line[line_len(line)] == '\n')
			return (line);
	}
}

/*int	main(void)
{
	char	*line;
	int		fd;

	printf("TEST 0: .txt with 4 short lines, all terminating with \\n\n");
	fd = open("data/test0.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	printf("\n");
	
	printf("TEST 1: .txt with 2 short lines, the last one without \\n\n");
	fd = open("data/test1.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	printf("\n");

	printf("TEST 2: .txt with 2 long lines, both terminating with \\n\n");
	fd = open("data/test2.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	printf("\n");

	printf("TEST 3: empty .txt\n");
	fd = open("data/test3.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	printf("\n");

	printf("TEST 4: standard input\n");
	line = get_next_line(0);
	printf("%s", line);
	free(line);
	printf("\n");

	printf("TEST 5: .c with 6 lines\n");
	fd = open("data/test5.c", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	printf("\n");

	printf("TEST 6: directory\n");
	fd = open("data", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	printf("\n");

	printf("TEST 7: invalid fd\n");
	while ((line = get_next_line(-1)))
	{
		printf("%s", line);
		free(line);
	}
	printf("\n");
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