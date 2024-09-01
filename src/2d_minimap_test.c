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

static void initialize_data_for_mlx(t_game *game, t_mlx_data *mlx_data)
{
    mlx_data->game = game;
    mlx_data->camera = game->camera_start_info;
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

static void prepare_images_buffers(t_mlx_data *mlx_data)
{
    int adj_size = CELL_SIZE - 1;

    mlx_data->image_walls = mlx_new_image(mlx_data->mlx, adj_size, adj_size); //having 31 instead of 32 allows a grey grid to automaticaly pop-up
    mlx_data->image_floor = mlx_new_image(mlx_data->mlx, adj_size, adj_size); // when we send the images to window with an offset of 32
    monocolor_img_buffer(mlx_data->image_walls, 0xFFFFFFFF); //we can change easly i liked the black-white combinaiton
    monocolor_img_buffer(mlx_data->image_floor, 0x000000FF); //simply coloring the images before bringing them to window

    mlx_data->image_player = mlx_new_image(mlx_data->mlx, 4, 4);
    monocolor_img_buffer(mlx_data->image_player, 0x00FF00FF);
    
    //below an working example of what we would do to bring a texture instead of colored pixels
    // mlx_texture_t *cust_texture = mlx_load_png("/home/ale/Cube3D/textures_ids/water_wall.png");
    // mlx_data.image_walls = mlx_texture_to_image(mlx_data.mlx, cust_texture);
}

static void display_2d_map(t_mlx_data *mlx_data)
{
    int y = 0;
    int x = 0;
    while(mlx_data->game->working_map[y])
    {
        x = 0;
        while(mlx_data->game->working_map[y][x])
        {
            if (mlx_data->game->working_map[y][x] == '1')
            {
                mlx_image_to_window(mlx_data->mlx, mlx_data->image_walls, x *CELL_SIZE, y *CELL_SIZE);
            }
            else if (mlx_data->game->working_map[y][x] == '0')
            {
                mlx_image_to_window(mlx_data->mlx, mlx_data->image_floor, x*CELL_SIZE, y *CELL_SIZE);
            }
            x++;
        }
        y++;
    }
}

static void display_player(t_mlx_data *mlx_data)
{
    t_game *game = mlx_data->game;

    mlx_image_to_window(mlx_data->mlx, mlx_data->image_player, game->camera_start_info->x * CELL_SIZE + CELL_SIZE/2,\
    game->camera_start_info->y * CELL_SIZE + CELL_SIZE/2); //i chose 4x4 because it's still a power of 2 and fits well with the cell size
    //also we do + cell size/2 so that we put the player at the center of the cell he is starting from :)
}

void    ft_custom_key(void *param)
{
    t_mlx_data *mlx_data = (t_mlx_data *)param;

    mlx_image_t * player = mlx_data->image_player;

    int new_x_test = player->instances[0].x;
    int new_y_test = player->instances[0].y;

    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_W) && mlx_data->game->working_map[(new_y_test - 4) / CELL_SIZE][new_x_test / CELL_SIZE] != '1')
        player->instances[0].y -= 4;
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_S) && mlx_data->game->working_map[(new_y_test + 4) / CELL_SIZE][new_x_test / CELL_SIZE] != '1')
        player->instances[0].y += 4;
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_A) && mlx_data->game->working_map[new_y_test/CELL_SIZE][(new_x_test - 4) / CELL_SIZE] != '1')
        player->instances[0].x -= 4;
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_D) && mlx_data->game->working_map[new_y_test/CELL_SIZE][(new_x_test + 4) / CELL_SIZE] != '1')
        player->instances[0].x += 4;
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx_data->mlx);

}



int main(int argc, char **argv)
{
	
	t_game game;
	t_mlx_data mlx_data;

    game.start_list_pointer = NULL;
	initialize_game(&game);
	if (!successfull_parsing(argc, argv, &game))
		return (free_list(game.start_list_pointer), free_game(&game), 1); // i still need to write a functoin to free both in one shot
    initialize_data_for_mlx(&game, &mlx_data);
    mlx_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
    prepare_images_buffers(&mlx_data);
    display_2d_map(&mlx_data);
    display_player(&mlx_data);
    mlx_loop_hook(mlx_data.mlx, ft_custom_key, &mlx_data);
    mlx_loop(mlx_data.mlx);
	return (0);
}
