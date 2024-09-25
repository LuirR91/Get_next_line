/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiribei <luiribei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:58:40 by luiribei          #+#    #+#             */
/*   Updated: 2024/06/20 13:58:33 by luiribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	read_content[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*current_line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	current_line = NULL;
	while (ft_is_newline(current_line) == -1)
	{
		if (read_content[fd][0] == '\0')
		{
			read_bytes = read(fd, read_content[fd], BUFFER_SIZE);
			if (read_bytes <= 0)
			{
				if (read_bytes == 0)
					return (current_line);
				free(current_line);
				return (NULL);
			}
			read_content[fd][read_bytes] = '\0';
		}
		current_line = ft_strjoin(current_line, read_content[fd]);
		ft_clean (current_line, read_content[fd]);
	}
	return (current_line);
}

int main()
{
	int	fd[3];
	char *line[3];
	int	line_count[3];
	
	fd[0] = open("file1.txt", O_RDONLY);
	fd[1] = open("file2.txt", O_RDONLY);
	fd[2] = open("file3.txt", O_RDONLY);
	if (fd[0] < 0 || fd[1] < 0 || fd[2] < 0)
	{
    perror("Error opening file");
    return (EXIT_FAILURE);
    }
	line_count[0] = 0;
	line_count[1] = 0;
	line_count[2] = 0;
    while ((line[0] = get_next_line(fd[0]))
	&& (line[1] = get_next_line(fd[1]))
	&& (line[2] = get_next_line(fd[2])))
	{
        // Output the line with a counter 
		printf("file1 %d: %s\n", ++line_count[0], line[0]);
		printf("file2 %d: %s\n", ++line_count[1], line[1]);
		printf("file3 %d: %s\n\n", ++line_count[2], line[2]);
		free(line[0]); // Free the line once used
		free(line[1]);
		free(line[2]);
	}
    // Close the file descriptor
    close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	return (EXIT_SUCCESS);
}