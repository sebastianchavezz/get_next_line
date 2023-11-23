/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schavez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:30:39 by schavez           #+#    #+#             */
/*   Updated: 2023/11/22 18:06:40 by schavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

void    print_newline_helper(char *buffer)
{

    while (*buffer &&  *buffer != '\0')
    {
        if (*buffer == '\n')
        {
            *buffer= '\\';
        }
        printf("%c",*buffer);
        buffer++;
    }
}

static char	*read_from_file(char *buffer, int fd)
{
	int	bytes_read;
    char *cup_buffer;

 
	if (NULL == buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE); 
	print_newline_helper(buffer);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char *get_next_line(int fd)
{
	static char	*buffer = NULL;
	char	*line = NULL;

	if (fd < 0 || read(fd, NULL, 0 ) || BUFFER_SIZE <= 0)	
		return (NULL);
	if (!buffer)
		buffer = (char *)malloc(sizeof(char) * (1 + BUFFER_SIZE));
	if(!buffer)
		return (NULL);
	if (!ft_strchr(buffer, '\n'))
		buffer = read_from_file(buffer, fd);
	if (NULL == buffer)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int main(void)
{
    int fd;
    char *line;
    int count;

    count = 0;
    fd = open("/nfs/homes/schavez/Desktop/get_next_line/file",O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening the file");
        return 1;
    }
    while(1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break;
        count++;
        printf("[%d]:%s\n", count, line);
        free(line);
        line = NULL;
    }
    close(fd);
    return 0;
}
