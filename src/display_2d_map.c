/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display_2d_map.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/20 16:39:18 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/10/27 16:11:24 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	first_local_loop(t_mlx_data *mlx_data, int x, int y)
{
	int	m;
	int	f;

	m = 0;
	while (m < mlx_data->game->mini_cell - 1)
	{
		f = 0;
		while (f < mlx_data->game->mini_cell - 1)
		{
			mlx_put_pixel(mlx_data->main_image, \
				(x * mlx_data->game->mini_cell + f), \
				(y * mlx_data->game->mini_cell + m), 0xFFFFFFFF);
			f++;
		}
		m++;
	}
}

static void	second_local_loop(t_mlx_data *mlx_data, int x, int y)
{
	int	z;
	int	r;

	z = 0;
	while (z < mlx_data->game->mini_cell - 1)
	{
		r = 0;
		while (r < mlx_data->game->mini_cell - 1)
		{
			mlx_put_pixel(mlx_data->main_image, \
				(x * mlx_data->game->mini_cell + r), \
				(y * mlx_data->game->mini_cell + z), 0x0000FFFF);
			r++;
		}
		z++;
	}
}

void	display_2d_map(t_mlx_data *mlx_data)
{
	int	y;
	int	x;

	y = 0;
	while (mlx_data->game->working_map[y])
	{
		x = 0;
		while (mlx_data->game->working_map[y][x])
		{
			if (mlx_data->game->working_map[y][x] == '1')
				first_local_loop(mlx_data, x, y);
			else if (mlx_data->game->working_map[y][x] == '0')
				second_local_loop(mlx_data, x, y);
			x++;
		}
		y++;
	}
}
