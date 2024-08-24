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
	game.start_list_pointer = NULL;
	if (!successfull_parsing(argc, argv, &game))
		return (free_list(game.start_list_pointer), free_game(&game), 1);
	
	//free_list(game.start_list_pointer);free_game(&game);
    //printf("width %d and height: %d and posiiton x %d and y %d\n", game.n_columns, game.n_rows, game.camera_start_info->x, game.camera_start_info->y);
	//initialize_layer(&game);
    mlx_t *mlx;
    mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
    mlx_set_setting(MLX_STRETCH_IMAGE, true);
    
    mlx_image_t *img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    int player_pixel_x = game.camera_start_info->x * CELL_SIZE + CELL_SIZE/2;
    int player_pixel_y = game.camera_start_info->y * CELL_SIZE + CELL_SIZE/2;
    printf("hello: %d, %d\n", game.camera_start_info->x, game.camera_start_info->y);
    {
        mlx_put_pixel(img, player_pixel_x, player_pixel_y, 0x00FF00FF);
    }
    for(int f = 0; f < SCREEN_HEIGHT; f++)
    {
        mlx_put_pixel(img, SCREEN_WIDTH -1, f, 0xFF0000FF);
    }
    mlx_image_to_window(mlx, img, 0, 0);
    mlx_loop(mlx);
	// int y = -1;
	// while(game.working_map[++y])
	//  	printf("%s\n", game.working_map[y]);
	return (0);
}
