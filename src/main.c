#include "cub3D.h"
#include  "fcntl.h"

void	get_best_x_lenght(int *m_lenght, char *line)
{
	int i;

	i = 0;
	while(line && line[i])
	{
		i++;
	}
	if (i > *m_lenght)
		*m_lenght = i;
}


void	add_new_line(char *line, t_lst **list)
{

	t_lst *current;

	t_lst *new_node = malloc(sizeof(t_lst));
	new_node->map_line = ft_strdup(line);
	new_node->next = NULL;
	if (list != NULL)
	{
		if (*list == (NULL))
		{
			//printf("hello\n");
			*list = new_node;
		}
		else
		{
			current = *list;
			while((current)->next)
			{
				current = current->next;
			}
			current->next = new_node;
		}
	}

}

int main(void)
{
	
    t_lst *list = NULL;
	int m_lenght = 0;

	int fd = open("map.cub", O_RDONLY, 0777);
	if (fd == -1)
	{
		printf("error in opening the map\n");
		return (1);
	}
    while (1)
    {
        char * line = get_next_line(fd);
		
        if (line == NULL)
            break ;
		get_best_x_lenght(&m_lenght, line);
		add_new_line(line, &list);
        free (line);
    }
	while(list)
	{
		printf("%s", list->map_line);
		list = list->next;
	}
	printf("\n");
	printf("%d\n", m_lenght);
    close(fd);
    return (0);
}