/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 13:48:59 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:53:45 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char f(unsigned int i, char c)
// {
//     if (c >= 'A' && c <= 'Z' )
//     {
//         c = c + 32;
//     }
//     return (c);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;
	size_t			len;

	if (!s || !f)
	{
		return (NULL);
	}
	i = 0;
	len = ft_strlen(s);
	new = malloc(len + 1);
	if (!new)
	{
		return (NULL);
	}
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}

// int main(void)
// {
//     char const s[] = "SDSdffdf";
//     printf("%s", ft_strmapi(s, f));
//     return (0);
// }