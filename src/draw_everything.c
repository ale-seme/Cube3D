/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_everything.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/20 17:28:14 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/10/29 17:20:37 by ale           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	display_player_fov(t_mlx_data *mlx_data)
{
	int			i;
	int			n_shifts;
	t_point		start;
	t_point		end;

	i = 0;
	n_shifts = mlx_data->game->minimap_shifts;
	while (i < SCREEN_WIDTH)
	{
		start.x = (int)mlx_data->ray->bresenham->x_1[i] >> (n_shifts + 1);
		start.y = (int)mlx_data->ray->bresenham->y_1[i] >> (n_shifts + 1);
		end.x = (int)mlx_data->ray->bresenham->x_2[i] >> (n_shifts + 1);
		end.y = (int)mlx_data->ray->bresenham->y_2[i] >> (n_shifts + 1);
		bresenham_line(mlx_data, start, end);
		i++;
	}
}

void	draw_everything(void *param)
{
	t_mlx_data	*mlx_data;

	mlx_data = (t_mlx_data *)param;
	mlx_delete_image(mlx_data->mlx, mlx_data->main_image);
	mlx_data->main_image = mlx_new_image(mlx_data->mlx, \
											SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(mlx_data->mlx, mlx_data->main_image, 0, 0);
	ray_casting(mlx_data);
	if (mlx_data->game->yes_minimap)
	{
		display_2d_map(mlx_data);
		display_player_fov(mlx_data);
	}
}
