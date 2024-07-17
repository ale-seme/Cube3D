/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 13:11:59 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/24 18:16:33 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
// int	main(void)
// {
// 	const char s[] = "hello Worldino codam is the new bachelor's";
// 	printf("%s\n", ft_strrchr(s, 'h'));
// 	const char f[] = "hello Worldino codam is the new bachelor's";
// 	printf("%s", strrchr(f, 'h'));
// 	return (0);
// }
// int	main(void)
// {	
// 	char s[] = "tripouille";
// 	char s2[] = "ltripouiel";
// 	// /* 1 */ printf("%s", ft_strrchr(s, 't'));
// 	// /* 2 */ printf("%s", ft_strrchr(s, 'l'));
// 	// ///* 3 */ check(ft_strrchr(s2, 'l') == s2 + 9);
// 	// ///* 4 */ check(ft_strrchr(s, 'z') == NULL);
// 	/* 5 */ printf("%s\n", ft_strrchr(s, 0));
// 	printf("%s", strrchr(s, 0));

// 	///* 6 */ printf("%s", ft_strrchr(s, 't' + 256));
// 	return (0);
// }