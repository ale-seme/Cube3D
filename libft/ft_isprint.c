/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 18:41:37 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:50:03 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	return (0);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isprint('#'));
// 	printf("%d", isprint('#'));
// 	return (0);
// }