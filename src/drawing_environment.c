#include "cub3D.h"

void	wall_drawing(t_mlx_data *mlx_data, float slice_height, int high_pixel, int low_pixel)
{
	float ray_angle = mlx_data->ray->current_angle;
	while(high_pixel < low_pixel)
	{
		mlx_put_pixel(mlx_data->main_image, mlx_data->ray->ray_n, high_pixel, 0xFFFF00FF);
		high_pixel++;
	}
}

void	fill_hex_color(uint32_t *final_color, int *floor_rbg_array, int bright)
{
	
	*final_color |= (floor_rbg_array[0] & 0xFF) << 24;
	*final_color |= (floor_rbg_array[1] & 0xFF) << 16;
	*final_color |= (floor_rbg_array[2] & 0xFF) << 8;
	*final_color |= (bright & 0xFF);
}

void	floor_and_ceiling_drawing(t_mlx_data *mlx_data, int high_pixel, int low_pixel)
{
	uint32_t	final_color;
	int	i;

	final_color = 0; 
	i = 0;
	
	fill_hex_color(&final_color, mlx_data->game->floor_rbg_array, 0xAA);
	while(low_pixel < SCREEN_HEIGHT)
	{
		mlx_put_pixel(mlx_data->main_image, mlx_data->ray->ray_n, low_pixel++, final_color);
	}
}

void	manage_wall_slice(t_mlx_data *mlx_data)
{
	float	slice_height;
	int		low_pixel;
	int		high_pixel;
	float	relative_angle;

	relative_angle = normalize_angle(mlx_data->ray->current_angle - mlx_data->camera->angle);//Eliminating FISHBOWL effect
	mlx_data->ray->wall_dst *= cos(relative_angle); //Eliminating FISHBOWL effect
	slice_height = CELL_SIZE / mlx_data->ray->wall_dst * mlx_data->camera->plane_distance; //we love ppermadi
	low_pixel = SCREEN_HEIGHT / 2 + slice_height /2;//PERMADI PART 9
	high_pixel = SCREEN_HEIGHT /2 - slice_height /2;//PERMADI PART 9 
	if (high_pixel < 0)
		high_pixel = 0;
	if (low_pixel > SCREEN_HEIGHT)
		low_pixel = SCREEN_HEIGHT;
	wall_drawing(mlx_data, slice_height, high_pixel, low_pixel);
	floor_and_ceiling_drawing(mlx_data, high_pixel, low_pixel);
	//something to draw the ceiling and the floor
}