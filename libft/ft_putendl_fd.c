/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 12:56:00 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:51:50 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	write (fd, s, len);
	write (fd, "\n", 1);
}

// int main(void)
// {
//     char s[] = "Write 'this' string + a newline";
//     ft_putendl_fd(s, 1);
//     return (0);
// }