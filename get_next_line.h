#ifndef BUFFER_SIZE
#   define BUFFER_SIZE 3
#endif


char	*ft_strchr(char *s, int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(char *s);
size_t	ft_strlcat(char *dst, char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
void *ft_memcpy(void *dest, void *src, size_t n);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
char *get_next_line(int fd);
static char *read_from_file(char *basin_buffer, int fd);
static char *obtain_remaining(char *pool_buffer);
static void print_new_line_helper(char *buffer);
static char *extract_line(char *pool_buffer);