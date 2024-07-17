/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 19:47:03 by asemerar      #+#    #+#                 */
/*   Updated: 2024/03/06 19:23:34 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return ((char *)(s + i));
}
// int	main(void)
// {
// 	char str[] = "Try to find out where is the s";
// 	printf("%s\n", ft_strchr("teste", '\0'));
// 	printf("%s", strchr("teste", '\0'));

// 	return (0);
// }