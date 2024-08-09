#include "cub3D.h"

int	ft_isspace(char c)
{
	return((c >= 9 && c <= 13) || (c == ' '));
}

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

void store_id_texture(t_game *game, int n_id, char *texture)
{
	if (n_id == 0)
		game->texture_nord = texture;
	else if (n_id == 1)
		game->texture_south = texture;
	else if (n_id == 2)
		game->texture_west = texture;
	else if (n_id == 3)
		game->texture_east = texture;
}

int	check_and_store_texture(char *line, int n_id, t_game *game)
{
	int	texture_fd;
	char *temp;
	
	temp = line + 2;
	if (!temp || !temp[0] || !ft_isspace(temp[0]))
		return (printf("Error, fake identifier detected\n"), 0);
	increment_id_count(game, n_id);
	while((*temp >= 9 && *temp <= 13) || *temp == ' ')
		temp++;
	texture_fd = open(temp, O_RDONLY, 0777);
	if (texture_fd == -1)
	{
		printf("An identifier has a texture with invalid path or permissions\n");
		return (0);
	}
	store_id_texture(game, n_id, temp);
	close(texture_fd);
	return (1);
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

int	traverse_and_atoi_check(int n_id, t_game *game, char **ss)
{
	int i;
	int *array;
	

	i = -1;
	array = malloc(sizeof(int) * 3);
	if (!array)
		return (printf("Error: failed to malloc the int array for RGBs\n"), 0);
	while(ss[++i])
	{
		
		array[i] = check_and_atoi(ss[i]);
		if (array[i] < 0)
			return (0);
	}
	if (n_id == 4)
		game->floor_rbg_array = array;
	else
		game->cealing_rbg_array = array;
	return (1);
}

int	split_store_and_check_rbg_amount(char *temp, int n_id, t_game *game)
{
	char **ss;

	ss = ft_split(temp, ',');
	if (!ss)
		return (printf("Error in splitting the rgb values for the identifier\n"), 0);
	if (!right_amount(ss))
		return (printf("Error: the program accepts 3 and only 3 RGBs for the ids\n"), 0);
	if (!traverse_and_atoi_check(n_id, game, ss))
		return (0);
	return (1);
}

int	check_convert_and_store_rbgs(char *line, int n_id, t_game *game)
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
