/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 19:35:58 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:59:49 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		return (c + 32);
	}
	else
		return (c);
}

// int	main(void)
// {
// 	printf("%d\n", ft_tolower('a'));
// 	printf("%d", tolower('a'));
// 	return (0);	
// }