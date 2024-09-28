#include "cub3D.h"

static float normailze_angle(double angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > 2 * PI)
		angle -= (2 * PI);
	return (angle);
}

void	inc_and_pixel(float angle, float *inc, int *add_pixel, bool b)
{
	if (b == true)
	{
		if (angle > 0 && angle < PI)
		{
			*inc = CELL_SIZE;
			*add_pixel = CELL_SIZE;
		}
		else if (angle > PI && angle < 2 * PI)
		{
			*inc = -CELL_SIZE;
			*add_pixel = -1;
		}
	}
	else
	{
		if (!(PI && angle < 3 * PI / 2))
		{
			*inc = CELL_SIZE;
			*add_pixel = CELL_SIZE;
		}
		else if (angle > PI && angle < 3 * PI/2)
		{
			*inc = -CELL_SIZE;
			*add_pixel = -1;
		}
	}
}

/*looks a confusing design but I want to avoid to use floor and maybe save some computation if the pixels are negative*/
int	wall_collision(t_mlx_data *mlx_data, float inter_y, float inter_x)
{
	int	map_y;
	int	map_x;

	if (inter_y < 0 || inter_x < 0)
		return (0);
	map_y = (int)(inter_y / CELL_SIZE);
	map_x = (int)(inter_x / CELL_SIZE);
	if (map_y >= mlx_data->game->n_rows || map_x >= mlx_data->game->n_columns)
		return (0);
	if (mlx_data->game->working_map[map_y][map_x] == '1')
		return (1);
	return (0);
}

float	calculate_h_inter(t_mlx_data *mlx_data, float angle)
{
	float	x_inc;
	float	y_inc;
	float	inter_x;
	float	inter_y;
	int		y_add_pixel;

	inc_and_pixel(angle, &y_inc, &y_add_pixel, true);
	x_inc = floor(CELL_SIZE * tan(angle));
	inter_y = floor(((mlx_data->camera->pixel_y / CELL_SIZE) * CELL_SIZE) + y_add_pixel);
	inter_x = mlx_data->camera->pixel_x + (inter_y - mlx_data->camera->pixel_y) / tan(angle);
	while(!wall_collision(mlx_data, inter_y, inter_x))
	{
		inter_y += y_inc;
		inter_x += x_inc;
	}
	mlx_data->ray->h_hit_x = inter_x;//i will add this but could delete if usless
	mlx_data->ray->h_hit_y = inter_x;//same as here

	//return (fabs((inter_x - mlx_data->camera->pixel_x) * lookup_cos(angle))); for now we keep square but this is a most efficient method
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
	pow(inter_y - mlx_data->camera->pixel_y, 2)));

}

// float	calculate_v_inter(t_mlx_data *mlx_data, float angle)
// {
// 	float	x_inc;
// 	float	y_inc;
// 	float	inter_x;
// 	float	inter_y;
// 	int		x_add_pixel;

// 	inc_and_pixel(angle, &x_inc, &x_add_pixel, false);
// 	y_inc = floor(CELL_SIZE * tan(angle));
// 	inter_x = floor(((mlx_data->camera->pixel_y / CELL_SIZE) * CELL_SIZE) + x_add_pixel);
// 	inter_y = mlx_data->camera->pixel_y + inter_x / tan(angle);
// 	while(!wall_collision(mlx_data, inter_y, inter_x))
// 	{
// 		inter_y += y_inc;
// 		inter_x += x_inc;
// 	}
// 	mlx_data->ray->h_hit_x = inter_x;//i will add this but could delete if usless
// 	mlx_data->ray->h_hit_y = inter_x;//same as here
	
// 	//return (fabs((inter_x - mlx_data->camera->pixel_x) * lookup_cos(angle))); for now we keep square but this is a most efficient method
// 	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
// 	pow(inter_y - mlx_data->camera->pixel_y, 2)));

// }

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
		v_inter = 1000000;
		//v_inter = calculate_v_inter(mlx_data, mlx_data->ray->current_angle);
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