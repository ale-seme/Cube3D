#include "cub3D.h"
#include  "fcntl.h"
#include <limits.h>

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
//need to double check with inputs that are 002 or 00000004
int	check_and_atoi(char *str)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	if (!str)
		return (0);
	while(str[i] >= 9 && str[i] <= 13)
		i++;
	while(str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			printf("only digit after spaces as RBG codes\n");
			return (-1);
		}
		if (number > (255 - (number + str[i] - '0') / 10))
		{
			printf("number given as RBG parameter should be max 255\n");
			return (-1);
		}
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number);
}

int	right_amount(char **ss)
{
	int	i;
	
	i = 0;
	while(ss[i])
	{
		i++;
	}
	return (i == 3);
}

int	check_ids_and_info(char *line, t_count *n_ids)
{
	int texture_fd;
	char **ss;
	int	flag;
	int i;

	flag = 0;
	if (!ft_strncmp(line, "NO ", 3))
	{
		n_ids->count_nord++;
		texture_fd = open(line + 3, O_RDONLY, 0777);
		if (texture_fd == -1)
		{
			printf("identifier has a texture with invalid path or permissions\n");
			return (0);
		}
		close(texture_fd);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		n_ids->count_south++;
		texture_fd = open(line + 4, O_RDONLY, 0777);
		if (texture_fd == -1)
		{
			printf("identifier has a texture with invalid path or permissions\n");
			return (0);
		}
		close(texture_fd);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		n_ids->count_west++;
		texture_fd = open(line + 3, O_RDONLY, 0777);
		if (texture_fd == -1)
		{
			printf("identifier has a texture with invalid path or permissions\n");
			return (0);
		}
		close(texture_fd);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		n_ids->count_east++;
		texture_fd = open(line + 3, O_RDONLY, 0777);
		if (texture_fd == -1)
		{
			printf("identifier has a texture with invalid path or permissions\n");
			return (0);
		}
		close(texture_fd);
	}
	else if (!ft_strncmp(line, "F ", 2))
	{
		n_ids->count_floor++;
		ss = ft_split(line + 2, ',');
		if (!ss)
			return (printf("error in split \n"), 0);
		if (!right_amount(ss))
			return (printf("The program accepts 3 and only 3 RBGs in the mapfile\n"), 0);
		i = 0;
		while(ss[i])
		{
			if (check_and_atoi(ss[i]) < 0)
				return (0);
			i++;
		}
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		n_ids->count_ceiling++;
		ss = ft_split(line + 2, ',');
		if (!ss)
			return (printf("error in split \n"), 0);
		if (!right_amount(ss))
			return (printf("The program accepts 3 and only 3 RBGs in the mapfile\n"), 0);
		i = 0;
		while(ss[i])
		{
			if (check_and_atoi(ss[i]) < 0)
				return (0);
			i++;
		}
	}
	return (1);

}

int	check_ids_amount(t_count *n_ids)
{
	if (n_ids->count_ceiling != 1 || n_ids->count_east != 1 || n_ids->count_floor != 1 \
	|| n_ids->count_nord != 1 || n_ids->count_nord != 1 || n_ids->count_south != 1 \
	|| n_ids->count_west != 1)
		return (0);
	return (1);
}

int	check_and_copy_map(t_lst *list)
{
	t_count n_ids;

	n_ids.count_nord = 0;
	n_ids.count_south = 0;
	n_ids.count_east = 0;
	n_ids.count_ceiling = 0;
	n_ids.count_floor = 0;
	n_ids.count_west = 0;

	if (!list)
		return (0);
	while(list)
	{
		if (list->map_line[0] == '\n')
			continue ;
		if (!check_ids_and_info(list->map_line, &n_ids))
			return (0);
		else if (!check_ids_amount(&n_ids))
		{
			printf("Error with the identifiers given in the map file\n");
			return (0);
		}
		
		list = list->next;
	}
	return (1);
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