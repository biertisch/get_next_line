/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:28:26 by beatde-a          #+#    #+#             */
/*   Updated: 2025/09/22 17:28:16 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

#define MAX_FILES 10

void	read_until_end(int *fd, int file_count)
{
	int		finished[MAX_FILES] = {0};
	int		remaining;
	int		i;
	char	*line;

	remaining = file_count;
	while (remaining > 0)
	{
		i = 0;
		while (i < file_count)
		{
			if (finished[i])
			{
				i++;
				continue ;
			}
			line = get_next_line(fd[i]);
			if (line)
			{
				printf("%s", line);
				free(line);
			}
			else
			{
				finished[i] = 1;
				remaining--;
			}
			i++;
		}
	}
}


void	close_files(int *fd, int file_count)
{
	int	i;

	i = 0;
	while (i < file_count)
	{
		if (fd[i] != STDIN_FILENO)
			close(fd[i]);
		i++;
	}
}

int	open_files(int argc, char **argv, int *fd)
{
	int	i;

	if (argc == 1)
	{
		fd[0] = STDIN_FILENO;
		return (1);
	}
	i = 0;
	while (i < argc - 1 && i < MAX_FILES)
	{
		fd[i] = open(argv[i + 1], O_RDONLY);
		if (fd[i] < 0)
		{
			perror("open");
			return (-1);
		}
		i++;
	}
	return (i);
}

int	main(int argc, char **argv)
{
	int		fd[MAX_FILES];
	int		file_count;

	file_count = open_files(argc, argv, fd);
	if (file_count <= 0)
		return (1);
	read_until_end(fd, file_count);
	close_files(fd, file_count);
}
