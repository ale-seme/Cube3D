#include "cub3D.h"

void	increment_id_count(t_game *game, int n_id)
{
	if (n_id == 0)
		 game->n_ids->count_nord++;
	else if (n_id == 1)
		game->n_ids->count_south++;
	else if (n_id == 2)
		game->n_ids->count_west++;
	else if (n_id == 3)
		game->n_ids->count_east++;
	else if (n_id == 4)
		game->n_ids->count_floor++;
	else if (n_id == 5)
		game->n_ids->count_ceiling++;
}


static int	check_convert_and_store_rbgs(char *line, int n_id, t_game *game)
{
	char *temp;
	temp = line + 1;
	if (!temp || !temp[0] || !ft_isspace(temp[0]))
		return(printf("Error, fake identifier detected\n"), 0);
	increment_id_count(game, n_id);
	while ((*temp >= 9 && *temp <= 13) || *temp == ' ')
		temp++;
	if (!(*temp))
		return(printf("Floor/Cealing has empty rbg values\n"));
	if (!split_store_and_check_rbg_amount(temp, n_id, game))
		return(0);
	return (1);
}

int	manage_floor_cealing_ids_and_usless_char(char *line, t_game *game)
{
	if (line[0] == 'F')
	{
		if (!check_convert_and_store_rbgs(line, 4, game))
			return (0);
	}
	else if (line[0] == 'C')
	{
		if (!check_convert_and_store_rbgs(line, 5, game))
			return (0);
	}
	else if (!line || (line[0] && line[0] != '\n'))
	{
		free_int_array(game->floor_rbg_array);
		free_int_array(game->cealing_rbg_array);
		return(printf("Error, presence of a usless char before the map"), 0);
	} //i'm converting all the newlines into null terms so idk
	return (1);
}