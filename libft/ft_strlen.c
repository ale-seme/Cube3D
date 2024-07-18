/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 18:56:33 by asemerar      #+#    #+#                 */
/*   Updated: 2024/07/18 15:40:57 by ale           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		i++;
	}
	return (i);
}
// int	main(void)
// {
// 	char str[] = "Hello World";
// 	printf("%zu", ft_strlen(str));
// 	printf("%lu", strlen(str));
// 	return (0);
// }