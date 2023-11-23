#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

static char *ft_extract_line(char *buffer) 
{
    int i = 0;
    if (!buffer || !buffer[0]) {
        return NULL;
    }
    while (buffer[i] && buffer[i] != '\n') {
        i++;
    }
    if (buffer[i] == '\n') {
        i++;
    }
    char *line = (char *)malloc((i + 1) * sizeof(char));
    if (!line) {
        return NULL;
    }
    ft_strlcpy(line, buffer, i + 1);
    return line;
}

static char *ft_update_buffer(char *buffer)
{
    int i = 0;
    int j = 0;
    char *new_buffer;

    if (!buffer) {
        return NULL;
    }
    while (buffer[i] && buffer[i] != '\n') {
        i++;
    }
    if (!buffer[i]) {
        free(buffer);
        return NULL;
    }
    new_buffer = (char *)malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
    if (!new_buffer) {
        return NULL;
    }
    i++;
    while (buffer[i]) {
        new_buffer[j++] = buffer[i++];
    }
    new_buffer[j] = '\0';
    free(buffer);
    return new_buffer;    
}

char *get_next_line(int fd) 
{
    static char *buffer;
    int fd_read;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    fd_read = 1;
    line = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!line)
        return (NULL);
    while (!ft_strchr(buffer, '\n') && fd_read != 0) {
        //printf("buffer at the beginning of the loop: %s\n", buffer);
        fd_read = read(fd, line, BUFFER_SIZE);
        if (fd_read == -1) {
            free(line);
            return (NULL);
        }
        line[fd_read] = '\0';
        //printf("line: %s\n", line);
        buffer = ft_strjoin(buffer, line);
        //printf("buffer at the end of the loop: %s\n", buffer);
    }
    free(line);
    line = ft_extract_line(buffer);
    buffer = ft_update_buffer(buffer);
    return (line);
}

int main(void)
{
    char *line;
    int fd;

    fd = open("/nfs/homes/schavez/Desktop/get_next_line/file", O_RDONLY); // Open the file for reading

    if (fd < 0)
    {
        perror("Error opening the file");
        return 1;
    }
    int i = 0;
    while ((line = get_next_line(fd)) != NULL ) // As long as we are getting lines from the file
    {
        printf("Line read: %s\n", line);
        free(line);
    }

    close(fd); // Close the file descriptor

    return 0;
}
