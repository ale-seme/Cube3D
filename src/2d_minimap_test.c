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

void    get_angle(t_mlx_data *mlx_data)
{
    char cardi;

    cardi = mlx_data->camera->cardinal_point;

    if (cardi == 'N')
        mlx_data->camera->angle = 3 * PI / 2;
    else if (cardi == 'W')
        mlx_data->camera->angle = PI;
    else if (cardi == 'S')
        mlx_data->camera->angle = PI /2;
    else if (cardi == 'E')
        mlx_data->camera->angle = 0;
}

static void initialize_data_for_mlx(t_game *game, t_mlx_data *mlx_data)
{

    mlx_data->ray = ft_calloc(1, sizeof(t_ray));
    if (!mlx_data->ray)
        printf("Error\nFailed calloc for rays struct\n");
    mlx_data->ray->wall_met = false;
    mlx_data->game = game;
    mlx_data->camera = game->camera_start_info;
    get_angle(mlx_data);
    mlx_data->camera->pixel_x = game->camera_start_info->x * CELL_SIZE + CELL_SIZE/2;//we do + cell size/2 so that we put the player at
    mlx_data->camera->pixel_y = game->camera_start_info->y * CELL_SIZE + CELL_SIZE/2;//the center of the cell he is starting from :)
    mlx_data->camera->fov_radi = FOW * PI/180.0;
    mlx_data->ray->unit_angle = mlx_data->camera->fov_radi / SCREEN_WIDTH; //this is the unit angle for each ray cast
    // mlx_data->camera->pdx = cos(mlx_data->camera->angle) * 4;
    // mlx_data->camera->pdy = sin(mlx_data->camera->angle) * 4; 
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

    mlx_data->main_image = mlx_new_image(mlx_data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx_data->image_walls = mlx_new_image(mlx_data->mlx, adj_size, adj_size); //having 31 instead of 32 allows a grey grid to automaticaly pop-up
    mlx_data->image_floor = mlx_new_image(mlx_data->mlx, adj_size, adj_size); // when we send the images to window with an offset of 32
    monocolor_img_buffer(mlx_data->image_walls, 0xFFFFFFFF); //we can change easly i liked the black-white combinaiton
    monocolor_img_buffer(mlx_data->image_floor, 0x000000FF); //simply coloring the images before bringing them to window

    // mlx_data->image_player = mlx_new_image(mlx_data->mlx, 4, 4); //i choose 4x4 because it fits well with the map and power of 2
    // monocolor_img_buffer(mlx_data->image_player, 0x00FF00FF);
    
    //TESTING PLAYER AS A 1PIXEL IMAGE

    // mlx_data->image_player = mlx_new_image(mlx_data->mlx, 1, 1); //i choose 4x4 because it fits well with the map and power of 2
    // monocolor_img_buffer(mlx_data->image_player, 0x00FF00FF);

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
                for(int m = 0; m < CELL_SIZE -1; m++)
                {
                    for(int f = 0; f < CELL_SIZE - 1; f++)
                        mlx_put_pixel(mlx_data->main_image, x * CELL_SIZE + f, y *CELL_SIZE + m, 0xFFFFFFFF);
                }
                //mlx_image_to_window(mlx_data->mlx, mlx_data->image_walls, x *CELL_SIZE, y *CELL_SIZE);
            }
            else if (mlx_data->game->working_map[y][x] == '0')
            {
                for(int z = 0; z < CELL_SIZE -1; z++)
                    for(int r = 0; r < CELL_SIZE - 1; r++)
                        mlx_put_pixel(mlx_data->main_image, x * CELL_SIZE + r, y * CELL_SIZE + z, 0x000000FF);
                //mlx_image_to_window(mlx_data->mlx, mlx_data->image_floor, x*CELL_SIZE, y *CELL_SIZE);
            }
            x++;
        }
        y++;
    }
}

static void display_player(t_mlx_data *mlx_data)
{
    t_game *game = mlx_data->game;

    printf("pixel x %f pixel y %f\n", game->camera_start_info->pixel_x, game->camera_start_info->pixel_y);
    mlx_put_pixel(mlx_data->main_image,  game->camera_start_info->pixel_x, game->camera_start_info->pixel_y, 0x0FF000FF);
    //printf("the pixel x map of the plater is %d and the y is %d\n", game->camera_start_info->x, game->camera_start_info->y);
    
    
    //mlx_image_to_window(mlx_data->mlx, mlx_data->image_player, game->camera_start_info->x * CELL_SIZE + CELL_SIZE/2,\
    game->camera_start_info->y * CELL_SIZE + CELL_SIZE/2); //i chose 4x4 because it's still a power of 2 and fits well with the cell size
    //also we do + cell size/2 so that we put the player at the center of the cell he is starting from :)
}

void ft_custom_key(void *param)
{
    t_mlx_data *mlx_data = (t_mlx_data *)param;


    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_LEFT))
    {
        mlx_data->camera->angle -= CAM_ROT;
        if (mlx_data->camera->angle < 0)
            mlx_data->camera->angle += 2 * PI;
    }
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_RIGHT))
    {
        mlx_data->camera->angle += CAM_ROT;
        if (mlx_data->camera->angle > 2 * PI)
            mlx_data->camera->angle -= 2 * PI;
    }

    printf("the angle radiants of the player %lf and in grades %lf\n", mlx_data->camera->angle, mlx_data->camera->angle * 180 / PI);


    float move_x = 0;
    float move_y = 0;

    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_W))
    {
		move_x = cos(mlx_data->camera->angle) * CAM_SPEED;
		move_y = sin(mlx_data->camera->angle) * CAM_SPEED;
        
    }
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_S))
    {
        move_x = -cos(mlx_data->camera->angle) * CAM_SPEED;
        move_y = -sin(mlx_data->camera->angle) * CAM_SPEED;
    }
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_A)) // we apply rotation here countercoockwise of 90 degrees from the current orientatoin, we rotate the movement vector
    {
        move_x = sin(mlx_data->camera->angle) * CAM_SPEED; // we do that like this: (x', y') = (-y, x)
        move_y = -cos(mlx_data->camera->angle) * CAM_SPEED;
    }
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_D))
    {
        move_x = -sin(mlx_data->camera->angle) * CAM_SPEED;
        move_y = cos(mlx_data->camera->angle) * CAM_SPEED;
    }

    // Update player position
    int new_x = roundf(mlx_data->camera->pixel_x + move_x);
    int new_y = roundf(mlx_data->camera->pixel_y + move_y);

    printf("new_x rounded: %f new_y rounded: %f\n",  move_x, move_y);

    if (mlx_data->game->working_map[new_y / CELL_SIZE][new_x / CELL_SIZE] != '1')
    {
        mlx_data->camera->pixel_x = new_x;
        mlx_data->camera->pixel_y = new_y;
        mlx_put_pixel(mlx_data->main_image, new_x, new_y, 0x00FF00FF);
    }

    // Close window (escape key)
    if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(mlx_data->mlx);
    }
}

void    draw_everything(void *param)
{
    t_mlx_data *mlx_data;
    
    mlx_data = (t_mlx_data *)param;
    mlx_delete_image(mlx_data->mlx, mlx_data->main_image);
    mlx_data->main_image = mlx_new_image(mlx_data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT); //now only minimap
    mlx_image_to_window(mlx_data->mlx, mlx_data->main_image, 0, 0);
    display_2d_map(mlx_data);
    display_player(mlx_data);
    ray_casting(mlx_data);
}

int main(int argc, char **argv)
{
	
	t_game game;
	t_mlx_data mlx_data;

    game.start_list_pointer = NULL;
	initialize_game(&game);
	if (!successfull_parsing(argc, argv, &game))
		return (free_everything(&game), 1); // i still need to write a functoin to free both in one shot
    initialize_data_for_mlx(&game, &mlx_data);
    mlx_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
    prepare_images_buffers(&mlx_data);
    mlx_loop_hook(mlx_data.mlx, draw_everything, &mlx_data);
    mlx_loop_hook(mlx_data.mlx, ft_custom_key, &mlx_data);
    mlx_loop(mlx_data.mlx);
	return (0);
}
