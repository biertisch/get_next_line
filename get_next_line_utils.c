/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:25:21 by beatde-a          #+#    #+#             */
/*   Updated: 2025/04/16 14:25:27 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_line(char **line)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
}

size_t	line_len(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (i);
}

void	reset_buffer(char *buffer)
{
	size_t	buffer_len;
	size_t	i;

	buffer_len = line_len(buffer);
	i = 0;
	if (buffer[buffer_len] == '\n')
		buffer_len++;
	while (buffer[buffer_len + i])
	{
		buffer[i] = buffer[buffer_len + i];
		i++;
	}
	buffer[i] = '\0';
}

void	extract_line(const char *buffer, char **line)
{
	char	*new_line;
	size_t	old_len;
	size_t	add_len;

	if (*line)
		old_len = line_len(*line);
	else
		old_len = 0;
	add_len = line_len(buffer);
	if (buffer[add_len] == '\n')
		add_len++;
	new_line = malloc(old_len + add_len + 1);
	if (!new_line)
	{
		clear_line(line);
		return ;
	}
	if (*line)
	{
		ft_strlcpy(new_line, *line, old_len + 1);
		clear_line(line);
	}
	ft_strlcpy(new_line + old_len, buffer, add_len + 1);
	*line = new_line;
}
