#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"


static char *extract_line(char *pool_buffer)
{
    char *line;
    int i;

    i = 0;
    while (pool_buffer[i] != '\n' && pool_buffer[i] != '\0')
        i++;
    line = ft_calloc(i + 1, sizeof(char));
    if (line == NULL)
        return (NULL);
    i = 0;
    while (pool_buffer[i] != '\n' && pool_buffer[i] != '\0')
    {
        line[i] = pool_buffer[i];
        i++;
    }
    return (line);
}

void    print_new_line_helper(char *buffer)
{
    while (*buffer && *buffer != '\0')
    {
        if (*buffer == '\n')
        {
            *buffer = '\\';
        }
        printf("%c",*buffer);
        buffer++;
    }
}

static char *obtain_remaining(char *pool_buffer)
{
    char *remaining;
    int i;
    int j;

    i = 0;
    while (pool_buffer[i] != '\n' && pool_buffer[i] != '\0')
        i++;
    if (pool_buffer[i] == '\0')
    {
        free(pool_buffer);
        return (NULL);
    }
    remaining = ft_calloc(ft_strlen(pool_buffer) - i + 1, sizeof(char));
    if (remaining == NULL)
        return (NULL);
    i++;
    j = 0;
    while (pool_buffer[i] != '\0')
    {
        remaining[j] = pool_buffer[i];
        i++;
        j++;
    }
    free(pool_buffer);
    return (remaining);
}

static char *read_from_file(char *basin_buffer, int fd)
{
    int     bytes_read;
    char    *cup_buffer;
    static int count;

    printf("ft_calloc[%d] ---", count++);
    cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (cup_buffer == NULL)
        return (NULL);
    bytes_read = 1;
    while (bytes_read > 0 )
    {
        bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(cup_buffer);
            return (NULL);
        }
        cup_buffer[bytes_read] = '\0';
        basin_buffer = ft_strjoin(basin_buffer, cup_buffer);
        if (ft_strchr(cup_buffer, '\n'))
            break;
    }
    print_new_line_helper(cup_buffer);
    if (bytes_read <= 0)
    {
        free(cup_buffer);
        return (NULL);
    }
    return (cup_buffer);
}

char *get_next_line(int fd)
{
    static char *pool_buffer;
    char    *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
        return NULL;
    if (!pool_buffer)
        pool_buffer = ft_calloc(1, sizeof(char));
    if (!ft_strchr(pool_buffer, '\n'))
    {
        pool_buffer = read_from_file(pool_buffer, fd);
        if (pool_buffer == NULL)
            free(pool_buffer);
            return (NULL);
    }
    line = extract_line(pool_buffer);
    pool_buffer = obtain_remaining(pool_buffer);
    return (line);
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