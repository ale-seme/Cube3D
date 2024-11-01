/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing_environment.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/20 17:33:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/10/28 19:57:14 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

mlx_texture_t	*get_texture(t_mlx_data *mlx_data)
{
	mlx_data->ray->current_angle = normalize_angle(mlx_data \
														->ray->current_angle);
	if (!mlx_data->ray->horiz_met_first)
	{
		if (mlx_data->ray->current_angle > PI / 2
			&& mlx_data->ray->current_angle < (3 * PI / 2))
			return (mlx_data->east);
		else
			return (mlx_data->west);
	}
	else
	{
		if (mlx_data->ray->current_angle > 0
			&& mlx_data->ray->current_angle < PI)
			return (mlx_data->south);
		else
			return (mlx_data->north);
	}
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	wall_drawing(t_mlx_data *mlx_data, float slice_height, \
										int high_pixel, int low_pixel)
{
	double			x_o;
	double			y_o;
	double			factor;
	uint32_t		*arr;
	mlx_texture_t	*texture;

	texture = get_texture(mlx_data);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / slice_height;
	x_o = get_x_o(texture, mlx_data);
	y_o = (high_pixel - (SCREEN_HEIGHT / 2) + (slice_height / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (high_pixel < low_pixel)
	{
		if ((int)y_o >= 0 && (int)y_o < (int)texture->height
			&& (int)x_o >= 0 && (int)x_o < (int)texture->width)
			mlx_put_pixel_special(mlx_data, mlx_data->ray->ray_n, high_pixel, \
				reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		else
			mlx_put_pixel_special(mlx_data, mlx_data->ray->ray_n, \
				high_pixel, 0x000000FF);
		y_o += factor;
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

void	manage_wall_slice(t_mlx_data *mlx_data)
{
	float	slice_height;
	int		low_pixel;
	int		high_pixel;
	float	relative_angle;

	relative_angle = normalize_angle(mlx_data->ray->current_angle \
										- mlx_data->camera->angle);
	mlx_data->ray->wall_dst *= cos(relative_angle);
	slice_height = CELL_SIZE / mlx_data->ray->wall_dst * \
											mlx_data->camera->plane_distance;
	low_pixel = SCREEN_HEIGHT / 2 + slice_height / 2;
	high_pixel = SCREEN_HEIGHT / 2 - slice_height / 2;
	if (high_pixel < 0)
		high_pixel = 0;
	if (low_pixel > SCREEN_HEIGHT)
		low_pixel = SCREEN_HEIGHT;
	wall_drawing(mlx_data, slice_height, high_pixel, low_pixel);
	floor_and_ceiling_drawing(mlx_data, high_pixel, low_pixel);
}
