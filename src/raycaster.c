/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/27 20:02:15 by asemerar      #+#    #+#                 */
/*   Updated: 2024/10/27 20:11:33 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	calc_h_inter(t_mlx_data *mlx_data, float angle)
{
	float	x_inc;
	float	y_inc;
	float	inter_x;
	float	inter_y;
	int		y_add_pixel;

	y_add_pixel = 0;
	x_inc = CELL_SIZE / tan(angle);
	inc_and_pixel_horiz(angle, &y_inc, &y_add_pixel, &x_inc);
	inter_y = floor(mlx_data->camera->pixel_y / CELL_SIZE) * CELL_SIZE + \
															y_add_pixel;
	inter_x = mlx_data->camera->pixel_x + \
						(inter_y - mlx_data->camera->pixel_y) / tan(angle);
	while (!wall_hit_or_out_bounds(mlx_data, inter_y, inter_x, 0))
	{
		inter_y += y_inc;
		inter_x += x_inc;
	}
	mlx_data->ray->h_hit_x = inter_x;
	mlx_data->ray->h_hit_y = inter_y;
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
				pow(inter_y - mlx_data->camera->pixel_y, 2)));
}

float	calc_v_inter(t_mlx_data *mlx_data, float angle)
{
	float	x_inc;
	float	y_inc;
	float	inter_x;
	float	inter_y;
	int		x_add_pixel;

	x_add_pixel = 0;
	if (angle == PI / 2 || angle == 3 * PI / 2)
		angle += 0.0001;
	y_inc = CELL_SIZE * tan(angle);
	inc_and_pixel_vert(angle, &x_inc, &x_add_pixel, &y_inc);
	inter_x = floor(mlx_data->camera->pixel_x / CELL_SIZE) * CELL_SIZE + \
															x_add_pixel;
	inter_y = mlx_data->camera->pixel_y + \
						(inter_x - mlx_data->camera->pixel_x) * tan(angle);
	while (!wall_hit_or_out_bounds(mlx_data, inter_y, inter_x, 1))
	{
		inter_y += y_inc;
		inter_x += x_inc;
	}
	mlx_data->ray->v_hit_x = inter_x;
	mlx_data->ray->v_hit_y = inter_y;
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
				pow(inter_y - mlx_data->camera->pixel_y, 2)));
}

void	store_info_and_set_distance(t_mlx_data *mlx_data, float h_inter_dist, \
															float v_inter_dist)
{
	if (h_inter_dist < v_inter_dist)
	{
		mlx_data->ray->horiz_met_first = 1;
		mlx_data->ray->wall_dst = h_inter_dist;
		mlx_data->ray->x_final_hit = mlx_data->ray->h_hit_x;
		mlx_data->ray->y_final_hit = mlx_data->ray->h_hit_y;
	}
	else
	{
		mlx_data->ray->horiz_met_first = 0;
		mlx_data->ray->wall_dst = v_inter_dist;
		mlx_data->ray->x_final_hit = mlx_data->ray->v_hit_x;
		mlx_data->ray->y_final_hit = mlx_data->ray->v_hit_y;
	}
}

void	ray_casting(t_mlx_data *mlx_data)
{
	float	h_inter_dist;
	float	v_inter_dist;

	mlx_data->ray->ray_n = 0;
	mlx_data->ray->unit_angle = mlx_data->camera->fov_radi / SCREEN_WIDTH;
	mlx_data->ray->current_angle = normalize_angle(mlx_data->camera->angle - \
	(mlx_data->camera->fov_radi / 2));
	while (mlx_data->ray->ray_n < SCREEN_WIDTH)
	{
		h_inter_dist = calc_h_inter(mlx_data, mlx_data->ray->current_angle);
		v_inter_dist = calc_v_inter(mlx_data, mlx_data->ray->current_angle);
		store_info_and_set_distance(mlx_data, h_inter_dist, v_inter_dist);
		if (mlx_data->game->yes_minimap)
			store_bresenham_coordinates(mlx_data->ray, mlx_data->camera);
		mlx_data->ray->current_angle = normalize_angle(mlx_data->\
								ray->current_angle + mlx_data->ray->unit_angle);
		manage_wall_slice(mlx_data);
		mlx_data->ray->ray_n++;
	}
}
