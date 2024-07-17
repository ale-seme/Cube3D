/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 15:36:23 by asemerar      #+#    #+#                 */
/*   Updated: 2024/01/18 14:03:36 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// // 	// unsigned char s[] = "Hello day";
// // 	// printf("%s\n", (char*)ft_memchr(s, 0, 1));
// // 	// unsigned char t[] = "Hello day";
// // 	// printf("%s", (char*)memchr(t, 0, 1));
// // 	// unsigned int a[9] = {1, 2, 3, 4, 5, 6, 7 ,8};
// // 	// unsigned int b[9] = {1, 2, 3, 4, 5, 6, 7 ,8};
// // 	// size_t i = 0;
// // 	// size_t n = 4;
// // 	// while (i < n)
// // 	// printf("%d", *((int*)(ft_memchr(a, 4, sizeof(int)*5))));
// // 	// printf("%d", *((int*)(memchr(b, 4, sizeof(int)*5))));
// 	char s[] = {0, 1, 2 ,3 ,4 ,5};
// // 	// printf("%s", (char*)ft_memchr(s, 0, 1));
// // 	// write(1, "\n", 1);
// // 	// printf("%s", (char*)memchr(s , 0 , 1));
// // 	// write(1, "\n", 1);
// 	printf("%s", (char*)ft_memchr(s, 0, 1));
// 	write(1, "\n", 1);
// 	printf("%s", (char*)memchr(s , 0 , 1));
// 	write(1, "\n", 1);
// // 	printf("%s", (char*)ft_memchr(s, 6, 6));
// // 	printf("%s", (char*)memchr(s , 6 , 6));
// // 	//write(1, "\n", 1);
// return (0);
// }
// 	char s[] = {0, 1, 2 ,3 ,4 ,5};
// 	/* 1 */ check(ft_memchr(s, 0, 0) == NULL); showLeaks();
// 	/* 2 */ check(ft_memchr(s, 0, 1) == s); showLeaks();
// 	/* 3 */ check(ft_memchr(s, 2, 3) == s + 2); showLeaks();
// 	/* 4 */ check(ft_memchr(s, 6, 6) == NULL); showLeaks();
// 	/* 5 */ check(ft_memchr(s, 2 + 256, 3) == s + 2); showLeaks(); //Cast check
// 	write(1, "\n", 1);
// 	return (0);