/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 13:47:32 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/26 13:17:51 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src && n > 0)
	{
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		*((char *)(dest + i)) = *((const char *)(src + i));
		i++;
	}
	return (dest);
}
// int	main(void)
// {
// 	//int src[7] = {1, 2, 3, 4, 5, 6};
// 	// int dest[9] = {7, 88, 43, 22, 323, 23, 22};
// 	//int dest[9];
// 	size_t n = 4;
// 	// int dest[9];
// 	char src[] = "My name is";
// 	char dest[30] = "           Giovanni Giorgio";
// 	ft_memcpy(dest, src, 16);
// 	//memcpy (dest, src,sizeof(int)*4);
// 	 printf("%s", dest);

// 	// int i = 0;
// 	// while (i < n)

// 	// 	printf("%d\n", dest[i++]);
// 	return (0);
// }