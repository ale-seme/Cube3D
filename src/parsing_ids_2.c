#include "cub3D.h"

//need to double check with inputs that are 002 or 00000004


static void store_id_texture(t_game *game, int n_id, char *texture)
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

static int	check_and_store_texture(char *line, int n_id, t_game *game)
{
	int	texture_fd;
	char *temp;
	
	temp = line + 2;
	if (!temp || !temp[0] || !ft_isspace(temp[0]))
		return (printf(ERR_FAKE_ID), 0);
	increment_id_count(game, n_id);
	while((*temp >= 9 && *temp <= 13) || *temp == ' ')
		temp++;
	texture_fd = open(temp, O_RDONLY | __O_DIRECTORY);
	if (texture_fd != -1)
		return(close(texture_fd), printf(ERR_TX_DIR), 0);
	printf("temp: %s\n", temp);
	texture_fd = open(temp, O_RDONLY);
	if (texture_fd == -1)
	{
		printf(ERR_TX_OPEN);
		return (0);
	}
	store_id_texture(game, n_id, temp);
	close(texture_fd);
	return (1);
}


static void	populate_cardinals(char **cardinals)
{
	cardinals[0] = "NO";
	cardinals[1] = "SO";
	cardinals[2] = "WE";
	cardinals[3] = "EA";
}

int	check_ids_and_info(char *line, t_game *game)
{
	int	x;
	char *cardinals[4];

	x = -1;
	populate_cardinals(cardinals);
	while(++x < 4)
	{
		if (!ft_strncmp(line, cardinals[x], 2))
		{
			if (!check_and_store_texture(line, x, game))
				return (0);
			return (1);
		}
	}
	if (!manage_floor_cealing_ids_and_usless_char(line, game))
		return (0);
	return (1);
}
