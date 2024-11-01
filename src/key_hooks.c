/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hooks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/20 14:46:48 by rgoossen      #+#    #+#                 */
/*   Updated: 2024/10/31 00:48:17 by asemerar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	update_player_position(t_mlx_data *mlx_data,
//float move_x, float move_y)
// {
// 	float	new_x;
// 	float	new_y;
// 	float	next_distance;

// 	new_x = mlx_data->camera->pixel_x + move_x;
// 	new_y = mlx_data->camera->pixel_y + move_y;

// 	next_distance = sqrt(pow(new_x - mlx_data->camera->pixel_x, 2) + 
	//pow(new_y - mlx_data->camera->pixel_y, 2));

// 	if (mlx_data->game->working_map
	//[(int)(new_y / CELL_SIZE)][(int)(new_x / CELL_SIZE)] != '1' &&
// 		mlx_data->game->working_map[(int)(new_y / CELL_SIZE)]
	//[(int)(new_x / CELL_SIZE)] != '2')
// 	{
// 		if (next_distance + 5.0 < miniraycaster(mlx_data))
// 		{
// 			mlx_data->camera->pixel_x = new_x;
// 			mlx_data->camera->pixel_y = new_y;
// 		}
// 	}
// }

float	miniraycaster(t_mlx_data *mlx_data)
{
	float	h_inter_dist;
	float	v_inter_dist;
	float	next_angle;

	next_angle = get_angle_direction(mlx_data, \
											mlx_data->camera->direction_flags);
	h_inter_dist = obtain_h_inter(mlx_data, next_angle);
	v_inter_dist = obtain_v_inter(mlx_data, next_angle);
	if (h_inter_dist < v_inter_dist)
	{
		return (h_inter_dist);
	}
	else
	{
		return (v_inter_dist);
	}
}

/**
 * @brief updates the player position based on the movement
 */
static void	update_player_position(t_mlx_data *mlx_data, \
										float move_x, float move_y)
{
	int		new_x;
	int		new_y;
	float	next_distance;

	new_x = roundf(mlx_data->camera->pixel_x + move_x);
	new_y = roundf(mlx_data->camera->pixel_y + move_y);
	next_distance = (sqrt(pow(new_x - mlx_data->camera->pixel_x, 2) + \
							pow(new_y - mlx_data->camera->pixel_y, 2)));
	if (mlx_data->game->working_map[new_y / CELL_SIZE][new_x / CELL_SIZE] \
	!= '1' && mlx_data->game->working_map[new_y / CELL_SIZE][new_x / CELL_SIZE] \
	!= '2')
	{
		if (next_distance + 5.0 < miniraycaster(mlx_data))
		{
			mlx_data->camera->pixel_x = new_x;
			mlx_data->camera->pixel_y = new_y;
		}
	}
}

/**
 * @brief movement key hook funciton forward, back and side to side
 */
static void	move_left_right_back_forward(t_mlx_data *mlx_data, \
											float *move_x, float *move_y)
{
	mlx_data->camera->direction_flags = 0;
	if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_W))
	{
		*move_x = cos(mlx_data->camera->angle) * CAM_SPEED;
		*move_y = sin(mlx_data->camera->angle) * CAM_SPEED;
		mlx_data->camera->direction_flags |= MOVE_FORWARD;
	}
	if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_S))
	{
		*move_x = -cos(mlx_data->camera->angle) * CAM_SPEED;
		*move_y = -sin(mlx_data->camera->angle) * CAM_SPEED;
		mlx_data->camera->direction_flags |= MOVE_BACKWARD;
	}
	if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_A))
	{
		*move_x = sin(mlx_data->camera->angle) * CAM_SPEED;
		*move_y = -cos(mlx_data->camera->angle) * CAM_SPEED;
		mlx_data->camera->direction_flags |= MOVE_LEFT;
	}
	if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_D))
	{
		*move_x = -sin(mlx_data->camera->angle) * CAM_SPEED;
		*move_y = cos(mlx_data->camera->angle) * CAM_SPEED;
		mlx_data->camera->direction_flags |= MOVE_RIGHT;
	}
}

/**
 * @brief window close key hook funciton
 */
static void	close_window(t_mlx_data *mlx_data)
{
	if (mlx_is_key_down(mlx_data->mlx, MLX_KEY_ESCAPE))
	{
		if (mlx_data->mlx)
			mlx_close_window(mlx_data->mlx);
	}
}

/**
 * @brief movement key hooks and movement funcitons
 */
void	ft_custom_key(void *param)
{
	float		move_x;
	float		move_y;
	t_mlx_data	*mlx_data;

	move_x = 0;
	move_y = 0;
	mlx_data = (t_mlx_data *)param;
	turn_left_right(mlx_data);
	move_left_right_back_forward(mlx_data, &move_x, &move_y);
	update_player_position(mlx_data, move_x, move_y);
	close_window(mlx_data);
}
