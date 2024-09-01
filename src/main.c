// #include "cub3D.h"
// #include  "fcntl.h"
// #include <limits.h>
// #include <math.h>
// #include <stdint.h>


// static void	initialize_game(t_game *game)
// {
// 	game->camera_start_info = NULL;
// 	game->cealing_rbg_array = NULL;
// 	game->floor_rbg_array = NULL;
// 	game->n_ids = NULL;
// 	game->start_list_pointer = NULL;
// 	game->start_map_pointer = NULL;
// 	game->texture_east = NULL;
// 	game->texture_nord = NULL;
// 	game->texture_south = NULL;
// 	game->texture_west = NULL;
// 	game->working_map = NULL;
// }

// static void initialize_mlx_struct(t_mlx_data *mlx_data, t_game *game)
// {
//    mlx_data->game = game;
//    mlx_data->camera = game->camera_start_info;


// }

// int main(int argc, char **argv)
// {
	
// 	t_game game;
// 	t_mlx_data mlx_data;

//     game.start_list_pointer = NULL;
// 	initialize_game(&game);
// 	if (!successfull_parsing(argc, argv, &game))
// 		return (free_list(game.start_list_pointer), free_game(&game), 1); // i still need to write a functoin to free in one shot
// 	initialize_mlx_data_struct(&mlx_data);
//     // int m = -1;
// 	// while(game.working_map[++m])
// 	//  	printf("%s\n", game.working_map[m]);

// 	return (0);
// }
