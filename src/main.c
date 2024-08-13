#include "cub3D.h"
#include  "fcntl.h"
#include <limits.h>


int main(int argc, char **argv)
{
	
	t_game game;

	game.start_list_pointer = NULL;
	if (!successfull_parsing(argc, argv, &game))
		return (1);
	 int y = -1;
	 while(game.working_map[++y])
	 	printf("%s\n", game.working_map[y]);
	return (0);
}