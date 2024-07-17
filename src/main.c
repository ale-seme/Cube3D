#include "cub3D.h"
#include  "fcntl.h"

int main(void)
{
	
	t_game *game;
	char *line;
	int map_fd;

	game = malloc(sizeof(t_game));
	map_fd = open("./map.cub", O_RDONLY, 0777);
	if (map_fd == -1)
		return (printf("Error in opening the map file\n"), 1);
	while (1)
	{
		line = get_next_line(map_fd);
		printf("%s\n", line);
		if (line == NULL)
			break ;
		//line = ft_memcpy()

	}
}