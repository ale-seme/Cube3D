#include <cub3D.h>

//just use this main instead of the other one, to check a test I was doing for the minimap
//you should be able to have a 4x4 pixels player that is able to move around and not go trough walls
//would be nice to adapt the structs a little bit to host everything and as good exercise 
//to be able to cast rays form the player and stop them once they intercept a wall


static void	initialize_game(t_game *game)
{
	game->camera_start_info = NULL;
	game->cealing_rbg_array = NULL;
	game->floor_rbg_array = NULL;
	game->n_ids = NULL;
	game->start_list_pointer = NULL;
	game->start_map_pointer = NULL;
	game->texture_east = NULL;
	game->texture_nord = NULL;
	game->texture_south = NULL;
	game->texture_west = NULL;
	game->working_map = NULL;
}

void    ft_green(void *param)
{
    mlx_image_t * image = (mlx_image_t *)param;
    for(uint32_t i = 0; i < image->height; i++)
    {
        for(uint32_t x = 0; x < image->width; x++)
        {
            mlx_put_pixel(image, x, i, 0x00FF00FF);
        }
    }
}



void    ft_custom_key(void *param)
{
    t_mlx_data *mlx_data = (t_mlx_data *)param;

    mlx_image_t * player = mlx_data->image_player;

    int new_x_test = player->instances[0].x;
    int new_y_test = player->instances[0].y;

    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_UP) && mlx_data->game->working_map[(new_y_test - 4) / CELL_SIZE][new_x_test / CELL_SIZE] != '1')
        player->instances[0].y -= 4;
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_DOWN) && mlx_data->game->working_map[(new_y_test + 4) / CELL_SIZE][new_x_test / CELL_SIZE] != '1')
        player->instances[0].y += 4;
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_LEFT) && mlx_data->game->working_map[new_y_test/CELL_SIZE][(new_x_test - 4) / CELL_SIZE] != '1')
        player->instances[0].x -= 4;
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_RIGHT) && mlx_data->game->working_map[new_y_test/CELL_SIZE][(new_x_test + 4) / CELL_SIZE] != '1')
        player->instances[0].x += 4;
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx_data->mlx);

}


void    monocolor_img_buffer(mlx_image_t *image, uint32_t color)
{
    for(uint32_t i = 0; i < image->height; i++)
    {
        for(uint32_t x = 0; x < image->width; x++)
        {
            mlx_put_pixel(image, x, i, color);
        }
    }
}

int main(int argc, char **argv)
{
	
	t_game game;
	t_mlx_data mlx_data;

    game.start_list_pointer = NULL;
	initialize_game(&game);
	if (!successfull_parsing(argc, argv, &game))
		return (free_list(game.start_list_pointer), free_game(&game), 1); // i still need to write a functoin to free in one shot
    
    mlx_data.game = &game;
    mlx_data.camera = game.camera_start_info;

    mlx_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
    mlx_data.image_walls = mlx_new_image(mlx_data.mlx, 31, 31); //having 31 instead of 32 allows a grey grid to automaticaly pop-up
    mlx_data.image_floor = mlx_new_image(mlx_data.mlx, 31, 31); // same here, could be expressed as CELL_SIZE -1

    monocolor_img_buffer(mlx_data.image_walls, 0xFFFFFFFF); //we can change easly i liked the black-white combinaiton
    monocolor_img_buffer(mlx_data.image_floor, 0x000000FF); //same

    
    // mlx_texture_t *cust_texture = mlx_load_png("/home/ale/Cube3D/textures_ids/water_wall.png");
    // mlx_data.image_walls = mlx_texture_to_image(mlx_data.mlx, cust_texture);

    int y = 0;
    int x = 0;
    while(game.working_map[y])
    {
        x = 0;
        while(game.working_map[y][x])
        {
            if (game.working_map[y][x] == '1')
            {
                mlx_image_to_window(mlx_data.mlx, mlx_data.image_walls, x *CELL_SIZE, y *CELL_SIZE);
            }
            else if (game.working_map[y][x] == '0')
            {
                mlx_image_to_window(mlx_data.mlx, mlx_data.image_floor, x*CELL_SIZE, y *CELL_SIZE);
            }
            x++;
        }
        y++;
    }
    mlx_data.image_player = mlx_new_image(mlx_data.mlx, 4, 4);
    monocolor_img_buffer(mlx_data.image_player, 0x00FF00FF);
    mlx_image_to_window(mlx_data.mlx, mlx_data.image_player, game.camera_start_info->x * CELL_SIZE + CELL_SIZE/2, game.camera_start_info->y * CELL_SIZE + CELL_SIZE/2);
    mlx_loop_hook(mlx_data.mlx, ft_custom_key, &mlx_data);
    mlx_loop(mlx_data.mlx);
	return (0);
}