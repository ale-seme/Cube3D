#include "cub3D.h"

static float normailze_angle(double angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > 2 * PI)
		angle -= (2 * PI);
	return (angle);
}

static void	calculate_o_intersection(t_mlx_data *mlx_data)
{
	int	one_x_pixel;
	int	one_y_pixel;

	one_x_pixel = 0;
	one_y_pixel = 0;

	if (mlx_data->camera->angle >)
}

void	ray_casting(t_mlx_data *mlx_data)
{
	float	o_inter;
	float	v_inter;
	int	which_ray;

	which_ray = 0;
	mlx_data->ray->current_angle = normailze_angle(mlx_data->camera->angle - (mlx_data->camera->fov_radi / 2));
	printf("Current angle of the ray value in radi %lf\n", mlx_data->ray->current_angle * 180 / PI);
	while(which_ray < SCREEN_WIDTH)
	{
		o_inter = calculate_o_inter(mlx_data, mlx_data->ray->current_angle);
		v_inter = calculate_v_inter(mlx_data, mlx_data->ray->current_angle);
		
		if (o_inter > v_inter)
			mlx_data->ray->wall_dst = v_inter;
		else
			mlx_data->ray->wall_dst = o_inter;
		//WRITE A FUNCTOIN TO DRAW THE CURRENT RAY AND KEEP IT
		//something to draw the walls
		which_ray++;
		mlx_data->ray->current_angle += mlx_data->ray->unit_angle; //I need to double check if this is the case
	}
}