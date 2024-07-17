/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 11:15:18 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:59:39 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include <bsd/string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	space_left;
	size_t	i;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (size <= d_len)
		return (size + s_len);
	space_left = size - d_len - 1;
	i = 0;
	while (i < space_left && src[i] != '\0')
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}

// int main(void)
// {
//     char dest[30];
// 	char * src = (char *)"AAAAAAAAA";
// 	dest[0] = 'B';
//     printf("%zu\n", ft_strlcat(dest, src, 1));
//     printf("%s\n", dest);

//     char dst[30];
//  	char * sorc = (char *)"AAAAAAAAA";
// 	dst[0] = 'B';
//     printf("%zu\n", strlcat(dst, sorc, 1));
//     printf("%s", dst);
//     return (0);
// }