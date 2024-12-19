

#include "cub3D.h"

/**
 * @brief funciton for camera rotation left and right arrow key hooks
 */
void	turn_left_right(t_mlx_data *mlx_data)
{
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
}

int	mini_wall_hit_or_out_bounds(t_mlx_data *mlx_data, float inter_y, \
													float inter_x, int flag)
{
	int	map_y;
	int	map_x;

	if (inter_y < 0 || inter_x < 0)
		return (1);
	map_y = (int)(floor(inter_y) / CELL_SIZE);
	map_x = (int)(floor(inter_x) / CELL_SIZE);
	if (flag && ((mlx_data->camera->angle > PI)
			&& (mlx_data->camera->angle < 2 * PI)))
	{
		map_y = (int)(ceil(inter_y) / CELL_SIZE);
	}
	else if (!flag && (mlx_data->camera->angle > PI / 2)
		&& (mlx_data->camera->angle < 3 * PI / 2))
	{
		map_x = (int)(ceil(inter_x) / CELL_SIZE);
	}
	if (map_y >= mlx_data->game->n_rows
		|| map_x >= mlx_data->game->n_columns)
		return (1);
	if (mlx_data->game->working_map[map_y][map_x] == '1' || \
					mlx_data->game->working_map[map_y][map_x] == '2')
		return (1);
	return (0);
}

float	obtain_h_inter(t_mlx_data *mlx_data, float angle)
{
	float	x_inc;
	float	y_inc;
	float	inter_x;
	float	inter_y;
	int		y_add_pixel;

	y_add_pixel = 0;
	x_inc = CELL_SIZE / tan(angle);
	inc_and_pixel_horiz(angle, &y_inc, &y_add_pixel, &x_inc);
	inter_y = floor(mlx_data->camera->pixel_y / CELL_SIZE) * \
											CELL_SIZE + y_add_pixel;
	inter_x = mlx_data->camera->pixel_x + \
					(inter_y - mlx_data->camera->pixel_y) / tan(angle);
	while (!mini_wall_hit_or_out_bounds(mlx_data, inter_y, inter_x, 0))
	{
		inter_y += y_inc;
		inter_x += x_inc;
	}
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
		pow(inter_y - mlx_data->camera->pixel_y, 2)));
}

float	obtain_v_inter(t_mlx_data *mlx_data, float angle)
{
	float	x_inc;
	float	y_inc;
	float	inter_x;
	float	inter_y;
	int		x_add_pixel;

	x_add_pixel = 0;
	y_inc = CELL_SIZE * tan(angle);
	inc_and_pixel_vert(angle, &x_inc, &x_add_pixel, &y_inc);
	inter_x = floor(mlx_data->camera->pixel_x / CELL_SIZE) * \
											CELL_SIZE + x_add_pixel;
	inter_y = mlx_data->camera->pixel_y + \
					(inter_x - mlx_data->camera->pixel_x) * tan(angle);
	while (!mini_wall_hit_or_out_bounds(mlx_data, inter_y, inter_x, 1))
	{
		inter_y += y_inc;
		inter_x += x_inc;
	}
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
				pow(inter_y - mlx_data->camera->pixel_y, 2)));
}

float	get_angle_direction(t_mlx_data *mlx_data, int direction_flags)
{
	float	player_angle;

	player_angle = normalize_angle(mlx_data->camera->angle);
	if (direction_flags & MOVE_FORWARD)
	{
		return (player_angle);
	}
	if (direction_flags & MOVE_BACKWARD)
	{
		return (normalize_angle(player_angle + PI));
	}
	if (direction_flags & MOVE_LEFT)
	{
		return (normalize_angle(player_angle - PI / 2));
	}
	if (direction_flags & MOVE_RIGHT)
	{
		return (normalize_angle(player_angle + PI / 2));
	}
	return (player_angle);
}
