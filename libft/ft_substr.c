/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 16:55:34 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:59:48 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	x;
	char	*p1;

	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (len > ft_strlen(s + start))
	{
		len = ft_strlen(s + start);
	}
	p1 = (char *)malloc(len + 1);
	if (!p1)
		return (NULL);
	x = 0;
	i = start;
	while (x < len && s[i])
	{
		p1[x++] = s[i++];
	}
	p1[x] = '\0';
	return (p1);
}
// int main(void)
// {
//     char const s[] = "Hello It's me, Mario";
//     printf("%s", ft_substr(s, 6, 7));
//     return (0);
// }