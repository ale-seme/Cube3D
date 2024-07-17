/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 17:51:54 by asemerar      #+#    #+#                 */
/*   Updated: 2024/01/18 15:19:05 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// typedef struct s_list
// {
//     void            *content;
//     struct s_list   *next;
// }                    t_list;

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != (NULL))
	{
		if (*lst != (NULL))
		{
			new->next = *lst;
		}
		*lst = new;
	}
}

// int main(void)
// {
//     t_list *list = NULL;
//     // I will try to add a node to an empty list
//     int n1 = 1;
//     t_list *new_node1 = malloc(sizeof(t_list));
//     new_node1->content = &n1;
//     new_node1->next = NULL;
//     ft_lstadd_front(&list, new_node1);
//     //I will test if I can add a node to a non-empty list 
//     int n2 = 103;
//     t_list * new_node2 = malloc(sizeof(t_list));
//     new_node2->content = &n2;
//     new_node2->next = NULL;
//     ft_lstadd_front(&list, new_node2);
//     //I will add now another node and make sure it will be at the front
//     int n3 = 14;
//     t_list *new_node3 = malloc(sizeof(t_list));
//     new_node3->content = &n3;
//     new_node3->next = (NULL);
//     ft_lstadd_front(&list, new_node3);
//     printf("Here as follows you have the updated list: \n");
//     t_list *current = list;
//     while (current)
//     {
//         printf("%d->", *(int *)current->content);
//         current = current->next;
//     }
//     printf("NULL\n");
//     free(new_node1);
//     free(new_node2);
//     free(new_node3);
//     return (0);
// }
