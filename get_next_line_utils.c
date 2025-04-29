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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
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
	return (ft_strlen(src));
}

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

void	extract_line(const char *buffer, char **line)
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
