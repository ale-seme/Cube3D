/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 13:26:02 by asemerar      #+#    #+#                 */
/*   Updated: 2024/03/14 17:06:15 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	number;

	number = n;
	if (number < 0)
	{
		write (fd, "-", 1);
		number *= -1;
	}
	if (number == 0)
	{
		write (fd, "0", 1);
	}
	if (number > 0)
	{
		if (number > 9)
		{
			ft_putnbr_fd(number / 10, fd);
		}
		ft_putchar(((number % 10) + 48), fd);
	}
}

// int main(void)
// {
//     ft_putnbr_fd(2147483647, 1);
//     write (1, "\n", 1);
//     ft_putnbr_fd(-214748364, 1);
//     write (1, "\n", 1);
//     ft_putnbr_fd(0, 1);
//     write (1, "\n", 1);
//     ft_putnbr_fd(-333, 1);
//     return (0);
// }