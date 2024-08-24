#include "cub3D.h"
#include  "fcntl.h"
#include <limits.h>
#include <math.h>

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1000
# define CELL_SIZE 32
# define FOW 66



int main(int argc, char **argv)
{
	
	t_game game;
	t_mlx_data mlx_data;

    game.start_list_pointer = NULL;
	if (!successfull_parsing(argc, argv, &game))
		return (free_list(game.start_list_pointer), free_game(&game), 1); // i still need to write a functoin to free in one shot
	// int y = -1;
	// while(game.working_map[++y])
	//  	printf("%s\n", game.working_map[y]);

    mlx_data.game = &game;
    mlx_data.camera = game.camera_start_info;
    mlx_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
    mlx_data.image = mlx_new_image(mlx_data.mlx, 32, 32);
    
    mlx_texture_t *cust_texture = mlx_load_png("/home/ale/Cube3D/textures_ids/water_wall.png");
    mlx_data.image = mlx_texture_to_image(mlx_data.mlx, cust_texture);

    int y = 0;
    int x = 0;
    while(game.working_map[y])
    {
        x = 0;
        while(game.working_map[y][x])
        {
            if (game.working_map[y][x] == '1')
                mlx_image_to_window(mlx_data.mlx, mlx_data.image, x *CELL_SIZE, y *CELL_SIZE);
            x++;
        }
        y++;
    }
    mlx_loop(mlx_data.mlx);
    

	return (0);
}
