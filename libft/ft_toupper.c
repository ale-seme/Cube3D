/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 19:05:20 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:54:59 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		return (c - 32);
	}
	else
		return (c);
}

// int	main(void)
// {
// 	printf("%d\n", ft_toupper('F'));
// 	printf("%d", toupper('F'));
// 	return (0);	
// }