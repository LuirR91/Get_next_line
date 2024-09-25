/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiribei <luiribei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:29:32 by luiribei          #+#    #+#             */
/*   Updated: 2024/06/21 13:52:24 by luiribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	read_content[BUFFER_SIZE + 1];
	char		*current_line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	current_line = NULL;
	while (ft_is_newline(current_line) == -1)
	{
		if (read_content[0] == '\0')
		{
			read_bytes = read(fd, read_content, BUFFER_SIZE);
			if (read_bytes <= 0)
			{
				if (read_bytes == 0)
					return (current_line);
				free(current_line);
				return (NULL);
			}
			read_content[read_bytes] = '\0';
		}
		current_line = ft_strjoin(current_line, read_content);
		ft_clean (current_line, read_content);
	}
	return (current_line);
}

int	main ()
{
	int	fd;
	char *line;
	int	line_count = 0;

	fd = open("file1.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (EXIT_FAILURE);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d; %s\n", ++line_count, line);
		free(line);
	}

	close(fd);
	return (EXIT_SUCCESS);
} 