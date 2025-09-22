/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:25:21 by beatde-a          #+#    #+#             */
/*   Updated: 2025/09/22 17:47:53 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	clear_line(char **line)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
}

static void	reset_buffer(char *buffer)
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

static void	extract_line(char *buffer, char **line)
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

static char	*read_file(int fd, char **buffer, size_t size)
{
	char		*line;
	ssize_t		bytes_read;

	line = NULL;
	while (1)
	{
		if (!(*buffer)[0])
		{
			bytes_read = read(fd, *buffer, size);
			if (bytes_read <= 0)
			{
				if (bytes_read < 0)
					clear_line(&line);
				clear_line(buffer);
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
	size_t		size;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	size = (size_t)BUFFER_SIZE;
	if (!buffer[fd])
	{
		buffer[fd] = malloc(size + 1);
		if (!buffer[fd])
			return (NULL);
		ft_memset(buffer[fd], 0, size + 1);
	}
	return (read_file(fd, &buffer[fd], size));
}
