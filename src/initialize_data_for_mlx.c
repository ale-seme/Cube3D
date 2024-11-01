/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_data_for_mlx.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/20 14:16:05 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/10/30 13:00:00 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_angle(t_mlx_data *mlx_data)
{
	char	cardi;

	cardi = mlx_data->camera->cardinal_point;
	if (cardi == 'N')
		mlx_data->camera->angle = 3 * PI / 2;
	else if (cardi == 'W')
		mlx_data->camera->angle = PI;
	else if (cardi == 'S')
		mlx_data->camera->angle = PI / 2;
	else if (cardi == 'E')
		mlx_data->camera->angle = 0;
}

static int	load_pngs(t_game *game, t_mlx_data *mlx_data)
{
	mlx_data->north = mlx_load_png(game->texture_nord);
	if (!mlx_data->north)
		return (0);
	mlx_data->south = mlx_load_png(game->texture_south);
	if (!mlx_data->south)
		return (0);
	mlx_data->east = mlx_load_png(game->texture_east);
	if (!mlx_data->east)
		return (0);
	mlx_data->west = mlx_load_png(game->texture_west);
	if (!mlx_data->west)
		return (0);
	return (1);
}

int	initialize_data_for_mlx(t_game *game, t_mlx_data *mlx_data)
{
	mlx_data->ray = ft_calloc(1, sizeof(t_ray));
	if (!mlx_data->ray)
		return (printf(ERR_RAY_CALLO), 0);
	mlx_data->ray->bresenham = ft_calloc(1, sizeof(t_bresenham));
	if (!mlx_data->ray->bresenham)
		return (printf(ERR_BRE_CALLO), 0);
	mlx_data->game = game;
	if (!load_pngs(game, mlx_data))
		return (0);
	mlx_data->camera = game->camera_start_info;
	get_angle(mlx_data);
	mlx_data->camera->pixel_x = game->camera_start_info->x * \
											CELL_SIZE + CELL_SIZE / 2;
	mlx_data->camera->pixel_y = game->camera_start_info->y * \
											CELL_SIZE + CELL_SIZE / 2;
	mlx_data->camera->fov_radi = FOV * PI / 180.0;
	mlx_data->camera->plane_distance = SCREEN_WIDTH / 2 * \
								(tan(mlx_data->camera->fov_radi / 2));
	mlx_data->ray->unit_angle = mlx_data->camera->fov_radi / SCREEN_WIDTH;
	return (1);
}
