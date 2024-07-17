/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 14:52:38 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/26 18:37:10 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <bsd/string.h>

char	*ft_strdup(const char *s)
{
	char	*p1;
	size_t	i;

	i = 0;
	p1 = (char *)malloc(ft_strlen(s) + 1);
	if (!p1)
	{
		return (NULL);
	}
	while (s[i])
	{
		*(p1 + i) = *(s + i);
		i++;
	}
	*(p1 + i) = '\0';
	return (p1);
}

// int main(void)
// {
//     const char s[] = "Hello World";
//     char * s1 = ft_strdup(s);
//     printf("%s", s1);
//     return (0);
// }