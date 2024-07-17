/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 18:51:52 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:50:32 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (!((*(unsigned char *)(s1 + i)) == (*(unsigned char *)(s2 + i))))
		{
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		}
		else
		{
			i++;
		}
	}
	return (0);
}

// int	main(void)
// {
// 	// const char s1[] = "Let's compare the first string";;
// 	// const char s2[] = "Let's comp second string";
// 	// printf("%d\n", ft_memcmp(s1, s2, 15));
// 	// printf("%d\n", ft_memcmp(s1, s2, 15));
// 	// const int s3[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
// 	// const int s4[4] = {1, 2, 2};
// 	// printf("%d\n", ft_memcmp(s3, s4, sizeof(int)*3));
// 	// printf("%d\n", ft_memcmp(s3, s4, sizeof(int)*3));
// 	char s[] = {-128, 0, 127, 0};
// 	char sCpy[] = {-128, 0, 127, 0};
// 	char s2[] = {0, 0, 127, 0};
// 	char s3[] = {0, 0, 42, 0};
// 	printf("%d\n", ft_memcmp(s2, s3, 4));
// 	printf("%d\n", memcmp(s2, s3, 4));
// 	return(0);
// }