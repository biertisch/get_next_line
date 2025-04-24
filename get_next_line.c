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

	if (fd == -1 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (!buffer[0])
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				return (line);
			buffer[bytes_read] = '\0';
		}
		extract_line(buffer, &line);
		if (!line)
			return (NULL);
		reset_buffer(buffer);
		if (line[line_len(line)] == '\n')
			return (line);
	}
}

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	printf("TEST 0: .txt with 4 short lines, all terminating with \\n\n");
	fd = open("data/test0.txt", O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		printf("line %i: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	printf("\n");

	
	printf("TEST 1: .txt with 2 short lines, the last one without \\n\n");
	fd = open("data/test1.txt", O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		printf("line %i: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	printf("\n");

	printf("TEST 2: .txt with 2 long lines, both terminating with \\n\n");
	fd = open("data/test2.txt", O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		printf("line %i: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	printf("\n");

	printf("TEST 3: empty .txt\n");
	fd = open("data/test3.txt", O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		printf("line %i: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	printf("\n");

	return (0);
}

/*TEST
1. fd = standard input(0)
2. fd= .c file
3. fd = .out file
4. fd = .jpg ??
5. fd = directory
6. fd = pipes, sockets, terminals ??
7. fd = -1 (fail doesn't exist, permission denied)

10. loop until EOF
11. call function once
12. call function twice

13. buffer_size = 42
14. buffer_size = 1
15. buffer_size = 9999
16. without D flag
17. buffer_size = 0
18. buffer_size = -1
*/