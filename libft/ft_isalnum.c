/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:59:43 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/26 18:02:04 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
//     char test_char = 'A';
//     // Testing ft_isalnum
//     if (ft_isalnum(test_char))
//     {
//         printf("ft_isalnum: '%c' is an alphanumeric\n", test_char);
//     }
//     else
//     {
//         printf("ft_isalnum: '%c' is not an alphanumeric\n", test_char);
//     }
//     // Testing isalnum from ctype.h
//     if (isalnum(test_char))
//     {
//         printf("isalnum: '%c' is an alphanumeric\n", test_char);
//     }
//     else
//     {
//         printf("isalnum: '%c' is not an alphanumeric\n", test_char);
//     }
//     return 0;
// }
