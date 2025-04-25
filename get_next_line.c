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
		if (line && line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
}

/*void	run_test(char *file_name)
{
	char	*line;
	int		fd;
	
	fd = open(file_name, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}

int	main(void)
{
	char	*line;
	
	printf("TEST 0: .txt 4 short lines \\n-terminated\n");
	run_test("data/test0.txt");
	
	printf("\nTEST 1: .txt 2 lines not \\n-terminated\n");
	run_test("data/test1.txt");

	printf("\nTEST 2: .txt 1 very long line\n");
	run_test("data/test2.txt");

	printf("\nTEST 3: .txt empty\n");
	run_test("data/test3.txt");

	printf("\nTEST 4: .txt multiple lines, lengths, chars and \\n\n");
	run_test("data/test4.txt");

	printf("\nTEST 5: .c file\n");
	run_test("data/test5.c");

	printf("\nTEST 6: standard input\n");
	line = get_next_line(0);
	printf("%s", line);
	free(line);

	printf("\nTEST 7: directory\n");
	run_test("data");

	printf("\nTEST 8: invalid fd\n");
	while ((line = get_next_line(-1)))
	{
		printf("%s", line);
		free(line);
	}
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