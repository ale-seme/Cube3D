

#include "cub3D.h"

float	get_x_o(mlx_texture_t *texture, t_mlx_data *mlx_data)
{
	double	x_o;

	if (mlx_data->ray->horiz_met_first)
		x_o = (int)fmodf((mlx_data->ray->h_hit_x * \
						(texture->width / CELL_SIZE)), texture->width);
	else
		x_o = (int)fmodf((mlx_data->ray->v_hit_y * \
						(texture->width / CELL_SIZE)), texture->width);
	return (x_o);
}

void	mlx_put_pixel_special(t_mlx_data *mlx_data, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(mlx_data->main_image, x, y, color);
}

static void	fill_hex_color(uint32_t *final_color, \
							int *floor_rbg_array, int bright)
{
	*final_color |= (floor_rbg_array[0] & 0xFF) << 24;
	*final_color |= (floor_rbg_array[1] & 0xFF) << 16;
	*final_color |= (floor_rbg_array[2] & 0xFF) << 8;
	*final_color |= (bright & 0xFF);
}

void	floor_and_ceiling_drawing(t_mlx_data *mlx_data, \
									int high_pixel, int low_pixel)
{
	uint32_t	final_color_floor;
	uint32_t	final_color_ceiling;
	int			i;

	final_color_floor = 0;
	final_color_ceiling = 0;
	i = 0;
	fill_hex_color(&final_color_floor, \
					mlx_data->game->floor_rbg_array, 0xAA);
	fill_hex_color(&final_color_ceiling, \
					mlx_data->game->cealing_rbg_array, 0xAA);
	while (low_pixel < SCREEN_HEIGHT)
		mlx_put_pixel(mlx_data->main_image, \
					mlx_data->ray->ray_n, low_pixel++, final_color_floor);
	while (i < high_pixel)
		mlx_put_pixel(mlx_data->main_image, \
					mlx_data->ray->ray_n, i++, final_color_ceiling);
}
