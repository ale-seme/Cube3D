/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 12:01:22 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/26 13:45:11 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// typedef struct s_list
// {
//     void            *content;
//     struct s_list   *next;
// }                    t_list;

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
	{
		return (NULL);
	}
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

// int main(void)
// {
//     int nb = 3;
//     t_list *empty = NULL;
//     t_list *node1 = malloc(sizeof(t_list));
//     t_list *node2 = malloc(sizeof(t_list));
//     t_list *node3 = malloc(sizeof(t_list));
//     node1->content = NULL;
//     node1->next = node3;
//     node2->content = NULL;
//     node2->next = node3;
//     node3->content = &nb;
//     node3->next = NULL;
//     printf("if the linked list it empty
// it will return null -> %p", ft_lstlast(empty));
//     printf("after iterating trough the linked
// list the value stored in the content of the last pointer ");
//     printf("is -> %d", *(int*)ft_lstlast(node1)->content);
//     return (0);
// }