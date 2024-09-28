#include "cub3D.h"

static float normailze_angle(double angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > 2 * PI)
		angle -= (2 * PI);
	return (angle);
}

void	y_inc_and_pixel(float angle, float *y_inc, int *y_add_pixel, bool b)
{
	if (b == true)
	{
		if (angle > 0 && angle < PI)
		{
			*y_inc = CELL_SIZE;
			*y_add_pixel = CELL_SIZE;
		}
		else if (angle > PI && angle < 2 * PI)
		{
			*y_inc = -CELL_SIZE;
			*y_add_pixel = -1;
		}
	}
	else
	{
		printf("hello");
	}

}

int	wall_collision(t_mlx_data *mlx_data, int inter_y, int inter_x)
{
	if (inter_y < 0 || inter_x < 0)
		return (1);
	if 
}

float	calculate_h_inter(t_mlx_data *mlx_data, float angle)
{
	float	x_inc;
	float	y_inc;
	float	inter_x;
	float	inter_y;
	int		y_add_pixel;

	y_inc_and_pixel(angle, &y_inc, &y_add_pixel, true);
	x_inc = floor(CELL_SIZE * tan(angle));
	inter_y = floor(((mlx_data->camera->pixel_y / CELL_SIZE) * CELL_SIZE) + y_add_pixel);
	inter_x = mlx_data->camera->pixel_x + inter_y * tan(angle);
	while(!mlx_data->ray->wall_met)
	{
		if (mlx_data->game->working_map[(int)(inter_y / CELL_SIZE)][(int)(inter_x / CELL_SIZE)] == '1' || inter_x / CELL_SIZE >= mlx_data->game->n_columns);
		{
			mlx_data->ray->wall_met = true;
		}
		inter_y += y_inc;
		inter_x += x_inc;
	}
	//return (fabs((inter_x - mlx_data->camera->pixel_x) * lookup_cos(angle))); for now we keep square
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
	pow(inter_y - mlx_data->camera->pixel_y, 2)));

}

void	ray_casting(t_mlx_data *mlx_data)
{
	float	h_inter;
	float	v_inter;
	int	which_ray;

	which_ray = 0;
	mlx_data->ray->current_angle = normailze_angle(mlx_data->camera->angle - (mlx_data->camera->fov_radi / 2));
	printf("Current angle of the ray value in radi %lf\n", mlx_data->ray->current_angle * 180 / PI);
	while(which_ray < SCREEN_WIDTH)
	{
		h_inter = calculate_h_inter(mlx_data, mlx_data->ray->current_angle);
		v_inter = calculate_v_inter(mlx_data, mlx_data->ray->current_angle);
		if (h_inter > v_inter)
			mlx_data->ray->wall_dst = v_inter;
		else
			mlx_data->ray->wall_dst = h_inter;
		//WRITE A FUNCTOIN TO DRAW THE CURRENT RAY AND KEEP IT
		//something to draw the walls
		which_ray++;
		mlx_data->ray->current_angle += mlx_data->ray->unit_angle; //I need to double check if this is the case
	}
	printf("last ray horizontal wal intersection %lf\n", h_inter);
}