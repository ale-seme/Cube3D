/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 18:43:43 by asemerar      #+#    #+#                 */
/*   Updated: 2024/02/03 12:10:59 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p1;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	if (!s1 && !s2)
		return (NULL);
	p1 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p1)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		p1[i] = s1[i];
		i++;
	}
	while (x < ft_strlen(s2))
	{
		p1[i++] = s2[x++];
	}
	p1[i] = '\0';
	return (p1);
}

// int main(void)
// {
//     char const s1[] = "First things ";
//     char const s2[] = "first";
//     char const s1[] = "";
//     char const s2[] = "first";
//     char const s1[] = "3+2+1=";
//     char const s2[] = "6";
//     char const s1[] = "\0";
//     char const s2[] = "1";
//     printf("%s", ft_strjoin(s1, s2));
//     return (0);
// }