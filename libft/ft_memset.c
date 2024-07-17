/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 13:20:41 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:51:22 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}
// int main(void)
// {
// 	char str[50] = "hello world";
// 	printf("%s", (char *)memset(str, '.', 4));
// 	printf("%s", (char *)ft_memset(str, '.', 4));
// 	return (0);
// }