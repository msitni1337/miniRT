#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*free_ptr(void *ptr, void *ptr1, void *ptr2, char **ptr3);
char	*ft_substr(char const *s, long start, long len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *str);

#endif
