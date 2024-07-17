/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 21:29:10 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:59:40 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <bsd/string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_source;
	size_t	i;

	i = 0;
	len_source = ft_strlen(src);
	if (size)
	{
		while (src[i] && (i < (size -1)))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_source);
}

// int main(void)
// {
// 	char str[] = "hello Worlddffdscdscdsdsvdsvdvdvdsvdsvds";
// 	char dest[10];
// 	printf("%zu\n", strlcpy(dest, str, 30));
// 	printf("%s", dest);
// 	return (0);
// }