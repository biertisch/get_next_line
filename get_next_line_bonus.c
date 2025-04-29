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

//when defining the size of buffer, check whether OPEN_MAX works
//if yes, include limits.h in header file

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

void	clear_line(char **line)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
}

void	reset_buffer(char *buffer)
{
	size_t	line_len;

	line_len = 0;
	while (buffer[line_len] && buffer[line_len] != '\n')
		line_len++;
	if (buffer[line_len] == '\n')
		line_len++;
	if (line_len > 0)
		ft_strlcpy(buffer, buffer + line_len, ft_strlen(buffer + line_len) + 1);
}

void	extract_line(char *buffer, char **line)
{
	char	*new_line;
	size_t	old_len;
	size_t	add_len;

	if (*line)
		old_len = ft_strlen(*line);
	else
		old_len = 0;
	add_len = 0;
	while (buffer[add_len] && buffer[add_len] != '\n')
		add_len++;
	if (buffer[add_len] == '\n')
		add_len++;
	new_line = malloc(old_len + add_len + 1);
	if (!new_line)
	{
		clear_line(line);
		return ;
	}
	if (*line)
		ft_strlcpy(new_line, *line, old_len + 1);
	ft_strlcpy(new_line + old_len, buffer, add_len + 1);
	clear_line(line);
	*line = new_line;
}

char	*read_file(int fd, char **buffer)
{
	char		*line;
	ssize_t		bytes_read;

	line = NULL;
	while (1)
	{
		if (!(*buffer)[0])
		{
			bytes_read = read(fd, *buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
			{
				if (bytes_read < 0)
					clear_line(&line);
				free(*buffer);
				*buffer = NULL;
				return (line);
			}
			(*buffer)[bytes_read] = '\0';
		}
		extract_line(*buffer, &line);
		reset_buffer(*buffer);
		if (line && line[0] && line[ft_strlen(line) - 1] == '\n')
			return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(BUFFER_SIZE + 1);
		if (!buffer[fd])
			return (NULL);
		ft_memset(buffer[fd], 0, BUFFER_SIZE + 1);
	}
	return (read_file(fd, &buffer[fd]));
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
	int	fd[5];
	int	i;

	fd[0] = open("data/test0.txt", O_RDONLY);
	fd[1] = open("data/test1.txt", O_RDONLY);
	fd[2] = open("data/test2.txt", O_RDONLY);
	fd[3] = open("data/test3.txt", O_RDONLY);
	fd[4] = open("data/test4.txt", O_RDONLY);
			
	i = 0;
	while (i < 3)
	{
		run_test(fd[0]);
		run_test(fd[1]);
		run_test(fd[2]);
		run_test(fd[3]);
		run_test(fd[4]);
		i++;
	}

	i = 0;
	while (i < 5)
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