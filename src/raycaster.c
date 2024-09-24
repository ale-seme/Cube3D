#include "cub3D.h"

void	normailze_angle(double angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > 2 * PI)
		angle -= (2 * PI);
}

// static void	calculate_o_intersection(t_mlx_data *mlx_data)
// {
// 	if (mlx_data->camera->pixel_x * CELL_SIZE)
// 	{

// 	}
// }

// void	ray_casting(t_mlx_data *mlx_data)
// {
// 	double	o_inter;
// 	double	v_inter;
// 	int	which_ray;

// 	which_ray = 0;
// 	mlx_data->ray->current_angle = normalize_angle(mlx_data->camera->angle - (mlx_data->camera->fov_radi / 2));
// 	while(which_ray < SCREEN_WIDTH)
// 	{
// 		o_inter = calculate_o_inter(mlx_data, mlx_data->ray->current_angle);
// 		v_inter = calculate_v_inter(mlx_data, mlx_data->ray->current_angle);
		
// 		if (o_inter > v_inter)
// 			mlx_data->ray->wall_dst = v_inter;
// 		else
// 			mlx_data->ray->wall_dst = o_inter;
// 		//something to draw the walls
// 		which_ray++;
// 		mlx_data->ray->current_angle += mlx_data->ray->unit_angle; //I need to double check if this is the case
// 	}

// }