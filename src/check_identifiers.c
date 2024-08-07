#include "cub3D.h"

int	ft_isspace(char c)
{
	return((c >= 9 && c <= 13) || (c == ' '));
}

void	increment_id_count(t_game *game, int n_id)
{
	if (n_id == 0)
		 game->n_ids.count_nord++;
	else if (n_id == 1)
		game->texture_south++;
	else if (n_id == 2)
		game->texture_west++;
	else if (n_id == 3)
		game->texture_east++;
}

int	compare_check_and_inc(char *line, int n_id, t_game *game)
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
	game->texture_nord = line + 2;
	close(texture_fd);
	return (1);
}
