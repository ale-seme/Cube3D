/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 16:05:33 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/26 14:28:40 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

// int	main(void)
// {
// 	char str[50] = "hello world, what a beautiful day to be alive";
// 	ft_bzero(str, 4);
//	char str1[50] = "hello world, what a beautiful day to be alive"
// 	printf("%s\n", str);
//  printf("%s", str1);
// 	return (0);
// }