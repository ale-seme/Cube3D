

#include "cub3D.h"

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > 2 * PI)
		angle -= (2 * PI);
	return (angle);
}

void	inc_and_pixel_vert(float angle, float *inc_x, int *add_pixel_x, \
															float *y_inc)
{
	if (!(angle > PI / 2 && angle < 3 * PI / 2))
	{
		*inc_x = CELL_SIZE;
		*add_pixel_x = CELL_SIZE;
	}
	else if (angle > PI / 2 && angle < 3 * PI / 2)
	{
		*inc_x = -CELL_SIZE;
		*add_pixel_x = -1;
		*y_inc *= -1;
	}
}

void	inc_and_pixel_horiz(float angle, float *y_inc, int *add_pixel_y, \
															float *x_inc)
{
	if (angle > 0 && angle < PI)
	{
		*y_inc = CELL_SIZE;
		*add_pixel_y = CELL_SIZE;
	}
	else if (angle > PI && angle < 2 * PI)
	{
		*y_inc = -CELL_SIZE;
		*add_pixel_y = -1;
		*x_inc *= -1;
	}
}

int	wall_hit_or_out_bounds(t_mlx_data *mlx_data, float inter_y, float inter_x, \
																	int flag)
{
	int	map_y;
	int	map_x;

	if (inter_y < 0 || inter_x < 0)
		return (1);
	map_y = (int)(floor(inter_y) / CELL_SIZE);
	map_x = (int)(floor(inter_x) / CELL_SIZE);
	if (flag && ((mlx_data->ray->current_angle > PI) && \
	(mlx_data->ray->current_angle < 2 * PI)))
		map_y = (int)(ceil(inter_y) / CELL_SIZE);
	else if (!flag && (mlx_data->ray->current_angle > PI / 2) && \
	(mlx_data->ray->current_angle < 3 * PI / 2))
		map_x = (int)(ceil(inter_x) / CELL_SIZE);
	if (map_y >= mlx_data->game->n_rows || map_x >= mlx_data->game->n_columns)
		return (1);
	if (mlx_data->game->working_map[map_y][map_x] == '1' || mlx_data->game->\
	working_map[map_y][map_x] == '2')
		return (1);
	return (0);
}
