/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 16:24:03 by asemerar      #+#    #+#                 */
/*   Updated: 2024/01/17 13:52:55 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*source;

	dst = (char *)dest;
	source = (const char *)src;
	if (source > dst)
		while (n--)
			*dst++ = *source++;
	else if (source < dst)
	{
		dst = dst + n - 1;
		source = source + n - 1;
		while (n--)
		{
			*(dst--) = *(source--);
		}
	}
	return (dest);
}
// int main(void) 
// {
// 	char dest[] = "I Wanna uat";
// 	char src[] = "I Wanna eat";
// 	ft_memmove(dest, src, 13);
// 	//memmove(dest, src, 13);
// 	printf("%s", dest);
// }
