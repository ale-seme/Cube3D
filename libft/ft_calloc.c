/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 12:10:20 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/26 14:36:39 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p1;

	if (size != 0 && ((nmemb * size) / size != nmemb))
	{
		return (NULL);
	}
	else
	{
		p1 = (void *) malloc(nmemb * size);
		if (!p1)
		{
			return (NULL);
		}
		ft_bzero(p1, nmemb * size);
		return (p1);
	}
}
// int main(void)
// {
//     size_t num_elements = 5;
//     size_t element_size = 4;
//     // Testing ft_calloc
//     void *ptr_ft = ft_calloc(num_elements, element_size);
//     if (ptr_ft)
//     {
//         printf("ft_calloc: Memory has been allocated correctly\n");
//         free(ptr_ft);
//     }
//     else
//     {
//         printf("ft_calloc: Function failed to allocate memory correctly\n");
//     }
//     // Testing calloc
//     void *ptr_std = calloc(num_elements, element_size);
//     if (ptr_std)
//     {
//         printf("calloc: Memory has been allocated correctly\n");
//         free(ptr_std);
//     }
//     else
//     {
//         printf("calloc: Function failed to allocate memory correctly\n");
//     }
//     return (0);
// }