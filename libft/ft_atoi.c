/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 10:35:16 by asemerar      #+#    #+#                 */
/*   Updated: 2024/01/20 18:34:34 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	int		negative;
	long	nb;

	i = 0;
	negative = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
		{
			negative = -1;
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * negative);
}

// int	main(void)
// {
// 	const char nptr[] = "     +1234alflfemnfsl";
// 	const char nptr2[] = "     -1234alflfemnfsl";
// 	const char nptr3[] = "		-al.23113";
// 	printf("%d\n", ft_atoi(nptr));
// 	printf("%d\n", ft_atoi(nptr2));
// 	printf("%d\n", ft_atoi (nptr3));
// 	return (0);
// }