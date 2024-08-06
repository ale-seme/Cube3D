#include "cub3D.h"
#include <fcntl.h>

int	increment_right_id(t_game *game)
{
	
}

int	increment_and_check(char *line, int id_count, t_game *game)
{
	int	texture_fd;

	id_count++;
	texture_fd = open(line + 3, O_RDONLY, 0777);
	if (texture_fd == -1)
	{
		printf("An identifier has a texture with invalid path or permissions\n");
		return (0);
	}
	game->texture_nord = line + 3;
	close(texture_fd);
	return (1);
}