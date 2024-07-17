/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 18:40:26 by asemerar      #+#    #+#                 */
/*   Updated: 2024/01/13 13:27:05 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

// int main(void)
// {
//     t_list *node1 = malloc(sizeof(t_list));
//     t_list *node2 = malloc(sizeof(t_list));
//     t_list *node3 = malloc(sizeof(t_list));

//     node1->content = NULL;
//     node1->next = node2;

//     node2->content = NULL;
//     node2->next = node3;

//     node3->content = NULL;
//     node3->next = NULL;
//     int size = ft_lstsize(node1);
//     printf("Size of the linked list is: %d\n", size);
//     free(node1);
//     free(node2);
//     free(node3);
//     return (0);
// }
