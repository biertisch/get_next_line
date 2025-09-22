/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:22:34 by beatde-a          #+#    #+#             */
/*   Updated: 2025/09/22 17:32:43 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	open_file(int argc, char **argv)
{
	int	fd;

	if (argc == 1)
		return (STDIN_FILENO);
	else if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			return (-1);
		}
		return (fd);
	}
	write(2, "Usage: ./get_next_line <filename>\n", 34);
	return (-1);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

	fd = open_file(argc, argv);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	if (fd != STDIN_FILENO)
		close(fd);
	return (0);
}
