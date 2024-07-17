/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 13:02:39 by asemerar      #+#    #+#                 */
/*   Updated: 2023/10/26 13:34:43 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst != (NULL))
	{
		if (*lst == (NULL))
		{
			*lst = new;
		}
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
	}
}

// int main(void)
// {
//     t_list *list = NULL;
//     // Allocate memory for new nodes
//     t_list *new_node1 = malloc(sizeof(t_list));
//     t_list *new_node2 = malloc(sizeof(t_list));
//     t_list *new_node3 = malloc(sizeof(t_list));
//     t_list *new_node4 = malloc(sizeof(t_list));
//     // I will try to add a node to an empty list
//     int n1 = 1;
//     new_node1->content = &n1;
//     new_node1->next = NULL; // Set the next pointer to NULL
//     // I will test if I can add a node to a non-empty list
//     int n2 = 103;
//     new_node2->content = &n2;
//     new_node2->next = NULL; // Set the next pointer to NULL
//     // I will add now another node and make sure it will be at the back
//     int n3 = 14;
//     new_node3->content = &n3;
//     new_node3->next = NULL;
//     int n4 = 7;
//     new_node4->content = &n4;
//     new_node4->next = NULL; // Set the next pointer to NULL
//     ft_lstadd_back(&list, new_node1);
//     ft_lstadd_back(&list, new_node2);
//     ft_lstadd_back(&list, new_node3);
//     ft_lstadd_back(&list, new_node4); // Add new_node4 to the list
//     printf("Here is the updated list: \n");
//     t_list *current = list;
//     while (current)
//     {
//         printf("%d->", *(int *)current->content);
//         current = current->next;
//     }
//     printf("NULL\n");
//     // Free the allocated memory
//     free(new_node1);
//     free(new_node2);
//     free(new_node3);
//     free(new_node4);
//     return 0;
// }