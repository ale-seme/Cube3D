

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "cub3D.h"

char	*ft_join_and_free(char *existing_buffer, char *buffer)
{
	char	*joined_buffer;

	joined_buffer = ft_strjoin(existing_buffer, buffer);
	free(existing_buffer);
	free(buffer);
	existing_buffer = NULL;
	return (joined_buffer);
}

char	*ft_read_and_store_till_nwl_or_eof(char *exist_buff, int fd)
{
	int		n_read;
	char	*buffer;

	if (!exist_buff)
	{
		exist_buff = ft_calloc(1, 1);
		if (!exist_buff)
			return (exist_buff = NULL, NULL);
	}
	n_read = 1;
	while (n_read > 0)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		n_read = read(fd, buffer, BUFFER_SIZE);
		if (n_read == -1)
			return (free(buffer), free(exist_buff), exist_buff = NULL, NULL);
		buffer[n_read] = '\0';
		exist_buff = ft_join_and_free(exist_buff, buffer);
		if (exist_buff == NULL)
			break ;
		else if (ft_strchr(exist_buff, '\n'))
			break ;
	}
	return (exist_buff);
}

char	*return_the_next_line(char *existing_buffer)
{
	char	*clean_line;
	int		i;

	i = 0;
	if (!existing_buffer || !*existing_buffer)
		return (NULL);
	while (existing_buffer[i] && existing_buffer[i] != '\n')
		i++;
	if (!existing_buffer[i])
		return (existing_buffer);
	clean_line = malloc(i + 2);
	if (!clean_line)
		return (NULL);
	clean_line[i + 1] = '\0';
	clean_line[i] = '\n';
	while (i--)
		clean_line[i] = existing_buffer[i];
	return (clean_line);
}

char	*return_what_red_after_new_line(char *existing_buffer)
{
	int		i;
	char	*next_buffer;
	char	*pointer_start;
	int		remaining_length;

	i = 0;
	if (!existing_buffer)
		return (NULL);
	pointer_start = ft_strchr(existing_buffer, '\n');
	if (!pointer_start)
		return (NULL);
	remaining_length = ft_strlen(pointer_start + 1);
	next_buffer = malloc(remaining_length + 1);
	if (!next_buffer)
		return (NULL);
	while (pointer_start[i + 1])
	{
		next_buffer[i] = pointer_start[i + 1];
		i++;
	}
	next_buffer[i] = '\0';
	return (free(existing_buffer), existing_buffer = NULL, next_buffer);
}

char	*get_next_line(int fd)
{
	static char	*pointer;
	static int	n_rep = 0;
	char		*line;
	char		*clean_line;

	if ((BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) == -1) && (n_rep > 0))
		return (free(pointer), pointer = NULL, NULL);
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) == -1)
		return (pointer = NULL, NULL);
	line = ft_read_and_store_till_nwl_or_eof(pointer, fd);
	if (line == NULL)
		return (pointer = NULL, NULL);
	clean_line = return_the_next_line(line);
	if (!clean_line)
		return (free(line), pointer = NULL, NULL);
	pointer = return_what_red_after_new_line(line);
	n_rep++;
	return (clean_line);
}

// int main (void)
// {
//     int fd = open ("map.txt", O_RDONLY, 0777);
//     int i;

//     i = 0;
//     while (i < 70)
//     {
//         char * line = get_next_line(fd);
//         if (line == NULL)
//             break ;
//         printf("%s", line);
//         free (line);
//         i++;
//     }
//     close(fd);
//     return (0);
// }