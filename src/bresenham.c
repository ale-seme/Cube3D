/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bresenham.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asemerar <asemerar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/27 20:12:13 by asemerar      #+#    #+#                 */
/*   Updated: 2024/10/27 20:21:32 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	store_bresenham_coordinates(t_ray *ray, t_camera *camera)
{
	ray->bresenham->x_1[ray->ray_n] = camera->pixel_x;
	ray->bresenham->y_1[ray->ray_n] = camera->pixel_y;
	ray->bresenham->x_2[ray->ray_n] = ray->x_final_hit;
	ray->bresenham->y_2[ray->ray_n] = ray->y_final_hit;
}

void	initialize_b_struct(t_bre *b, t_point *start, t_point *end)
{
	b->dx = abs(end->x - start->x);
	b->dy = abs(end->y - start->y);
	if (start->x < end->x)
		b->sx = 1;
	else
		b->sx = -1;
	if (start->y < end->y)
		b->sy = 1;
	else
		b->sy = -1;
	b->err = b->dx - b->dy;
}

void	bresenham_line(t_mlx_data *mlx_data, t_point start, t_point end)
{
	t_bre	b;

	initialize_b_struct(&b, &start, &end);
	while (1)
	{
		if (start.x < 0 || start.y < 0 || start.x / mlx_data->game->mini_cell > \
		mlx_data->game->n_columns - 1 || start.y / mlx_data->game->mini_cell > \
		mlx_data->game->n_rows - 1 || (mlx_data->game->working_map[start.y / \
		mlx_data->game->mini_cell][start.x / mlx_data->game->mini_cell] == '1'))
			break ;
		mlx_put_pixel(mlx_data->main_image, start.x, start.y, 0x00FF00FF);
		if (start.x == end.x && start.y == end.y)
			break ;
		b.e2 = 2 * b.err;
		if (b.e2 > -b.dy)
		{
			b.err -= b.dy;
			start.x += b.sx;
		}
		if (b.e2 < b.dx)
		{
			b.err += b.dx;
			start.y += b.sy;
		}
	}
}
