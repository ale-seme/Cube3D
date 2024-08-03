#include "cub3D.h"
#include  "fcntl.h"
#include <limits.h>

void	remove_newline(char line[])
{
	int i;

	i = 0;
	while(line && line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		i++;
	}
}


void	add_new_node(char *line, t_lst **list)
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

int	check_ids_and_info(char *line, t_count *n_ids, t_game *game)
{
	int texture_fd;
	int i;

	//flag = 0;
	if (!ft_strncmp(line, "NO ", 3))
	{
		n_ids->count_nord++;
		texture_fd = open(line + 3, O_RDONLY, 0777);
		if (texture_fd == -1)
		{
			printf("identifier nord has a texture with invalid path or permissions\n");
			return (0);
		}
		game->texture_nord = line + 3;
		close(texture_fd);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		n_ids->count_south++;
		texture_fd = open(line + 3, O_RDONLY, 0777);
		if (texture_fd == -1)
		{
			printf("identifier south has a texture with invalid path or permissions\n");
			return (0);
		}
		game->texture_south = line + 3;
		close(texture_fd);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		n_ids->count_west++;
		texture_fd = open(line + 3, O_RDONLY, 0777);
		if (texture_fd == -1)
		{
			printf("identifier west has a texture with invalid path or permissions\n");
			return (0);
		}
		game->texture_west = line + 3;
		close(texture_fd);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		n_ids->count_east++;
		texture_fd = open(line + 3, O_RDONLY, 0777);
		if (texture_fd == -1)
		{
			printf("identifier east has a texture with invalid path or permissions\n");
			return (0);
		}
		game->texture_east = line + 3;
		close(texture_fd);
	}
	else if (!ft_strncmp(line, "F ", 2))
	{
		n_ids->count_floor++;
		game->floor_rbg = ft_split(line + 2, ',');
		if (!game->floor_rbg)
			return (printf("error in split \n"), 0);
		if (!right_amount(game->floor_rbg))
			return (printf("The program accepts 3 and only 3 RBGs in the mapfile\n"), 0);
		i = 0;
		while(game->floor_rbg[i])
		{
			if (check_and_atoi(game->floor_rbg[i]) < 0)
				return (0);
			i++;
		}
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		n_ids->count_ceiling++;
		game->cealing_rbg = ft_split(line + 2, ',');
		if (!game->cealing_rbg)
			return (printf("error in split \n"), 0);
		if (!right_amount(game->cealing_rbg))
			return (printf("The program accepts 3 and only 3 RBGs in the mapfile\n"), 0);
		i = 0;
		while(game->cealing_rbg[i])
		{
			if (check_and_atoi(game->cealing_rbg[i]) < 0)
				return (0);
			i++;
		}
	}
	return (1);

}

int	check_ids_amount(t_count *n_ids)
{
	//printf("%d%d%d%d%d%d\n", n_ids->count_nord, n_ids->count_south, n_ids->count_west, n_ids->count_east, n_ids->count_floor, n_ids->count_ceiling);
	if (n_ids->count_ceiling != 1 || n_ids->count_east != 1 || n_ids->count_floor != 1 \
	|| n_ids->count_nord != 1 || n_ids->count_nord != 1 || n_ids->count_south != 1 \
	|| n_ids->count_west != 1)
		return (0);
	return (1);
}

int	check_ids_and_get_map_start(t_lst *list, t_game *game)
{
	t_count n_ids;

	n_ids.count_nord = 0;
	n_ids.count_south = 0;
	n_ids.count_west = 0;
	n_ids.count_east = 0;
	n_ids.count_floor = 0;
	n_ids.count_ceiling = 0;

	if (!list)
		return (0);
	while(list)
	{
		if (list->map_line[0] == '\n' || list->map_line[0] == '\0')
		{
			list = list->next;
			if (!list)
				break ;
			continue ;
		}
		if (!check_ids_and_info(list->map_line, &n_ids, game))
			return (0);
		list = list->next;
		if (check_ids_amount(&n_ids))
			break ;
	}
	if (!check_ids_amount(&n_ids)) //could also check if (!list)
	{
		printf("Error with the identifiers given in the map file\n");
		return (0);
	}
	while(list && (list->map_line[0] == '\n' || list->map_line[0] == '\0'))
		list = list->next;
	if (!list)
		return (printf("Error, reached end of map with not enough info\n"));
	game->start_map_pointer = list;
	return (1);
}

int	good_argument(int argc, char** argv)
{
	int	len;

	if (argc < 2)
		return (printf("No argv provided\n"), 0);
	len = ft_strlen(argv[1]);
	if (len < 4 || argv[1][len -1] != 'b' || argv[1][len -2] != 'u' || argv[1][len - 3] != 'c' || argv[1][len - 4] != '.')
		return (printf("Error: argv is not .cub file\n"), 0);
	return (1);
	
}

int	check_elements_and_get_info(t_game *game)
{
	t_lst *lst;
	int i;
	bool	got_cardinal = false;

	game->n_rows = 0; //for now here but i should do before 
	game->n_columns = 0; //for now here but I should do before
	lst = game->start_map_pointer;
	while(game && lst) //probably i don't need to check game hiihh
	{
		i = -1;
		while(lst->map_line[++i])
		{
			if (ft_strchr(ELEMENTS, lst->map_line[i]))
			{
				if (lst->map_line[i] == ' ')
					lst->map_line[i] = '2';
			}
			else if (ft_strchr(CARDINALS, lst->map_line[i]) && !got_cardinal)
			{
				got_cardinal = true;
				game->camera_start_info->cardinal_point = lst->map_line[i];
				game->camera_start_info->x = i;
				game->camera_start_info->y = game->n_rows; //could seem confusing but n_rows is updated line by line
			}
			else
				return(printf("the map contains an element that is not allowed, or not allowed more than once\n"), 0);
		}
		if (i > game->n_columns)
			game->n_columns = i;
		game->n_rows++;
		lst = lst->next;
	}
	return (1);
}

int	check_adapt_and_copy_map(t_game *game)
{
	int	i;
	t_lst *list_map_line;

	list_map_line = game->start_map_pointer;


	game->camera_start_info = malloc(sizeof(t_camera)); //maybe I should do this before as well
	if (!game->camera_start_info)
		return (printf("error in malloching camera info\n"), 0);
	if (!check_elements_and_get_info(game))
		return (0);


	game->working_map = malloc(sizeof(char *) * (game->n_rows + 1));
	if (!game->working_map)
		return(printf("Error in malloc 2D array\n"), 0);
	i = -1;
	while(++i < game->n_rows)
	{
		game->working_map[i] = malloc(sizeof(char) * (game->n_columns + 1));
		if (!game->working_map[i])
			return (printf("Error in malloc a single line of 2D array\n"), 0);
		game->working_map[i][game->n_columns] = '\0';
	}
	game->working_map[i] = NULL;
	i = 0;
	int r;
	while(game->working_map[i])
	{
		ft_memset(game->working_map[i], '2', game->n_columns -1);
		r = 0;
		while(list_map_line->map_line[r])
		{
			game->working_map[i][r] = list_map_line->map_line[r];
			r++;
		}
		printf("%s\n", game->working_map[i]);

		list_map_line = list_map_line->next;
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	
    t_lst *list = NULL;
	t_game game;

	if (!good_argument(argc, argv))
		return(1);
	
	int	n_lines = 0;
	int fd = open(argv[1], O_RDONLY, 0777);
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
		remove_newline(line);
		add_new_node(line, &list);
        free (line);
    }
	game.start_list_pointer = list;
	check_ids_and_get_map_start(list, &game);
	check_adapt_and_copy_map(&game);
	
	printf("number of cols: %d\nnumber of rows %d\n", game.n_columns, game.n_rows);
	printf("camera orientation is: %c and position x: %d and positoin y: %d\n", game.camera_start_info->cardinal_point, game.camera_start_info->x, game.camera_start_info->y);
	// while(list)
	// {
	// 	printf("%s\n", list->map_line);
	// 	list = list->next;
	// }
	int x = -1;
	while(game.working_map[++x])
	{
		
		printf("%zu\n", ft_strlen(game.working_map[x]));
	}
    close(fd);
    return (0);
}