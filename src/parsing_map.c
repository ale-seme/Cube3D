#include "cub3D.h"

static void    convert_spaces_and_copy_map(t_game *game, t_lst *temp)
{
	int i;
	int r;

	i = 0;
	while(game->working_map[i])
	{
		r = 0;
		ft_memset(game->working_map[i], '2', game->n_columns);
		while(temp->map_line[r])
		{
			game->working_map[i][r] = temp->map_line[r];
			r++;
		}
		temp = temp->next;
		i++;
	}
}

static int convert_spaces_and_check_values(int *i, t_lst *lst, t_game *game, bool *got_cardinal)
{
	while(lst->map_line[++(*i)])
	{
		if (ft_strchr(ELEMENTS, lst->map_line[*i]))
		{
			if (lst->map_line[*i] == ' ')
				lst->map_line[*i] = '2';
		}
		else if (ft_strchr(CARDINALS, lst->map_line[*i]) && !(*got_cardinal))
		{
			*got_cardinal = true;
			game->camera_start_info->cardinal_point = lst->map_line[*i];
			game->camera_start_info->x = *i;
			game->camera_start_info->y = game->n_rows; //could seem confusing but n_rows is updated line by line
			lst->map_line[*i] = '0';
		}
		else
			return(printf("the map contains an element that is not allowed, or not allowed more than once\n"), 0);
		}
		return (1);
}

static int	check_elements_and_get_info(t_game *game)
{
	t_lst	*lst;
	int		i;
	bool	got_cardinal;

	got_cardinal = false;
	game->n_rows = 0; //for now here but i should do before 
	game->n_columns = 0; //for now here but I should do before
	lst = game->start_map_pointer;
	while(game && lst) //probably i don't need to check game hiihh
	{
		if (lst->map_line[0] == '\0') //changed to this
			return (printf("Empty lines in the map are no allowed\n"), 0);
		i = -1;
		if (!convert_spaces_and_check_values(&i, lst, game, &got_cardinal))
			return (0);
		if (i > game->n_columns)
			game->n_columns = i;
		game->n_rows++;
		lst = lst->next;
	}
	if (!got_cardinal)
		return(printf("Error, one cardinal is needed for the player starting position\n"), 0);
	return (1);
}

int	map_enclosed_by_walls(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while(game->working_map[y])
	{
		x = 0;
		while (game->working_map[y][x])
		{
			if ((x == 0 || (x == game->n_columns -1) || y == 0 \
			|| (y == game->n_rows -1)) && (game->working_map[y][x] == '0'))
				return(printf("the map is NOT sourrounded by walls\n"), 0);
			else
				if (game->working_map[y][x] == '0' && (game->working_map[y][x -1] == '2' \
				|| game->working_map[y][x + 1] == '2' \
				|| game->working_map[y - 1][x] == '2' \
				|| game->working_map[y + 1][x] == '2'))
					return(printf("Error: the map is not sourrounded by walls. y: %d, x: %d\n", y, x), 0);
			x++;
		}
		y++;
	}
	return(1);
}

int	check_adapt_and_copy_map(t_game *game)
{
	int	i;
	t_lst *temp;

	temp = game->start_map_pointer;
	game->camera_start_info = malloc(sizeof(t_camera)); //maybe I should do this before as well
	if (!game->camera_start_info)
		return (printf("error in malloc camera info\n"), 0);
	if (!check_elements_and_get_info(game))
		return (0);
	game->working_map = malloc(sizeof(char *) * (game->n_rows + 1));
	if (!game->working_map)
		return(printf("Error in malloc 2D array\n"), 0);
	game->working_map[game->n_rows] = NULL;
	i = -1;
	while(++i < game->n_rows)
	{
		game->working_map[i] = malloc(sizeof(char) * (game->n_columns + 1));
		if (!game->working_map[i])
			return (printf("Error in malloc a single line of 2D array\n"), 0);
		game->working_map[i][game->n_columns] = '\0';
	}
	convert_spaces_and_copy_map(game, temp);
	return (1);
}


