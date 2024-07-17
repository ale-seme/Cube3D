/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 20:13:32 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/26 18:11:48 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <bsd/string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while (*big && len > 0)
	{
		if (*big == *little)
		{
			i = 0;
			while (big[i] == little[i] && little[i] && (i + 1) <= len)
				i++;
			if (i == little_len)
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}

// int main(void)
// {
//     const char big[] = "This is me Alessandro Rocky_Balboa";
//     const char little[] = "Rocky_Balboa";
//     printf("%s", ft_strnstr(big, little, 35));
//     //printf("%s", strnstr(big, little, 11));
//     return (0);
// }
// int main(void)
// {
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "aabc";
// 	char * empty = (char*)"";
// 	printf("%s\n", ft_strnstr(haystack, "aaabc",5));
// 	printf("%s\n", ft_strnstr(haystack, "cd",8)); 
// 	char hay[30] = "aaabcabcd";
// 	char need[10] = "aabc";
// 	char * emp = (char*)"";
// 	printf("%s\n", strnstr(hay, "aaabc",5));
// 	printf("%s\n", strnstr(hay, "cd",8)); 
// 	write(1, "\n", 1);
// 	return (0);
// }
// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
//     char haystack[30] = "aaabcabcd";
//     char needle[10] = "aabc";
//     char *empty = "";
//     return (0);
// }