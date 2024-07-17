/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 19:22:35 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/20 18:52:39 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void f(unsigned int i, char* c)
// {
//     if(*c >= 'a' && *c <= 'z')
//     {
//         *c = *c + i;
//     }
//     return;
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
	{
		return ;
	}
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// int main(void)
// {
//     char s[] = "aaaaaaaaaaa";
//     ft_striteri(s, f);
//     printf("%s", s);
//     return (0);
// }