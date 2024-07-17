/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/22 16:43:59 by asemerar      #+#    #+#                 */
/*   Updated: 2024/02/08 14:44:23 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

// size_t ft_strlen(const char *s);
// char	*ft_strjoin(const char *s1, const char *s2);
// char	*ft_strchr(const char *s, int c);
// void	*ft_calloc(size_t elementCount, size_t elementSize);
// void	ft_bzero(void *s, size_t n);
char	*get_next_line(int fd);

#endif