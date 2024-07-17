/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 20:51:00 by asemerar      #+#    #+#                 */
/*   Updated: 2024/03/14 17:03:13 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_int_len(long number)
{
	size_t	len;

	len = 1;
	if (number < 0)
	{
		number *= -1;
		len++;
	}
	if (number == 0)
	{
		return (1);
	}
	while (number > 9)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	len;
	long	number;

	number = n;
	len = ft_get_int_len(number);
	s = (char *)malloc(len + 1);
	if (!s)
		return (NULL);
	if (number == 0)
		*s = '0';
	if (number < 0)
	{
		number *= -1;
		*s = '-';
	}
	while (number > 0)
	{
		s[len - 1] = (number % 10) + 48;
		number /= 10;
		len--;
	}
	s[ft_get_int_len(n)] = '\0';
	return (s);
}

// int main(void)
// {
// 	printf("%s\n", ft_itoa(-2147483648));
// 	printf("%s\n", ft_itoa(2147483647));
// 	printf("%s\n", ft_itoa(0));
// 	printf("%s\n", ft_itoa(-1232221));
// 	printf("%s\n", ft_itoa(1));
// 	return (0);
// }