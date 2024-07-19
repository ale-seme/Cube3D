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
			*list = new_node;
		else
		{
			current = *list;
			while((current)->next)
				current = current->next;
			current->next = new_node;
		}
	}

}

int	check_and_itoa(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '0' && str[i + 1] != '\0')
	{
		return(printf("Error: floor or ceiling color cannot be a 0 followed by sommething else"), 0);
	}
	while(str[i])
	{
		
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			accepting only 
		}
	}
}

int	check_identifier_and_info(char *line, int *n_cardinals, int *n_others)
{
	int texture_fd;
	char **ss;

	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) \
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		(*n_cardinals)++;
		texture_fd = open(line + 3, O_RDONLY, 0777);
		if (texture_fd == -1)
		{
			printf("texture not opening in identifier with the given path\n");
			return (0);
		}
		//close(texture_fd); does MLX need to oppen the texture or does by itself? 
	}
	else if (!ft_strncmp(line, "F ", 2))
	{
		ss = ft_split(line + 2, ",");
		if (!ss)
			return(print("error in split\n", 0));
		int i = 0;
		if (!check_if_right_amount())
		while(ss[i])
		{
			if (!check_and_itoa(ss[i]))
				return (0);
			
		}
		
	}
	return (0);

}

int	check_and_copy_map(t_lst *list)
{
	int n_cardinals;
	int n_others;
	
	n_cardinals = 0;
	n_others = 0;
	if (!list)
		return (0);
	while(list)
	{
		if (list->map_line[0] == '\n');
			continue ;
		if (!check_identifier_and_info(list->map_line, &n_cardinals, &n_others))
		{
			printf("Error with the orientation info in th map file\n");
			return (0);
		}
	}
}

int main(void)
{
	
    t_lst *list = NULL;
	int m_lenght = 0;
	int	n_lines = 0;

	int fd = open("valid_map.cub", O_RDONLY, 0777);
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
		n_lines++;
		get_best_x_lenght(&m_lenght, line);
		add_new_line(line, &list);
        free (line);
    }
	check_and_copy_map(list);

    close(fd);
    return (0);
}