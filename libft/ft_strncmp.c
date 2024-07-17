/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 14:00:46 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:54:15 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		}
		i++;
	}
	return (0);
}
// int	main(void)
// {
// 	char st1 [] = "aalessss";
// 	char st2 [] = "alessssa";
// 	printf("actual function is %d\n", strncmp(st1, st2, 4));
// 	printf("custom funciton is %d\n", ft_strncmp(st1, st2, 4));
// 	return (0);
// }