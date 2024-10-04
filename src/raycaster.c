#include "cub3D.h"


float normalize_angle(float angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > 2 * PI)
		angle -= (2 * PI);
	return (angle);
}

void	inc_and_pixel_vert(float	angle, float *inc_x, int *add_pixel_x, float *y_inc)
{

	
	if (!(angle > PI / 2  && angle < 3 * PI / 2))
	{
		*inc_x = CELL_SIZE;
		*add_pixel_x = CELL_SIZE;
	}
	else if (angle > PI /2 && angle < 3 * PI/2)
	{
		*inc_x = -CELL_SIZE;
		*add_pixel_x = -1;
		*y_inc *= -1;
	}
}

void	inc_and_pixel_horiz(float angle, float *y_inc, int *add_pixel_y, float *x_inc)
{

	if (angle > 0 && angle < PI)
	{
		*y_inc = CELL_SIZE;
		*add_pixel_y = CELL_SIZE;
	}
	else if (angle > PI && angle < 2 * PI)
	{
		*y_inc = -CELL_SIZE;
		*add_pixel_y = -1;
		*x_inc *= -1;
	}
}

/*looks a confusing design but I want to avoid to use floor and maybe save some computation if the pixels are negative*/
int	wall_hit_or_out_bounds(t_mlx_data *mlx_data, float inter_y, float inter_x)
{
	int	map_y;
	int	map_x;

	if (inter_y < 0 || inter_x < 0)
		return (1);
	map_y = (int)(inter_y / CELL_SIZE);
	map_x = (int)(inter_x / CELL_SIZE);

	if (map_y >= mlx_data->game->n_rows || map_x >= mlx_data->game->n_columns)
		return (1);
	
	//if (mlx_data->game->working_map[map_y] && map_x <= (int)ft_strlen(mlx_data->game->working_map[map_y]))
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
	if (angle == PI / 2 || angle == 3 * PI / 2) //I don't think it's needed becasue It never is perfectly this grades, I will try with something else
    	angle += 0.0001;
	x_inc = CELL_SIZE / tan(angle);
	inc_and_pixel_horiz(angle, &y_inc, &y_add_pixel, &x_inc);
	inter_y = floor(mlx_data->camera->pixel_y / CELL_SIZE) * CELL_SIZE + y_add_pixel;

	// if (angle > PI && angle < 2 * PI)
	// 	x_inc *= -1;
	
	inter_x = mlx_data->camera->pixel_x + (inter_y - mlx_data->camera->pixel_y) / tan(angle);
	if (mlx_data->ray->ray_n == 960) //i'm checking the values for the middle ray to see what's up
	{
		printf("HORIZONTAL: value of inter_x at the beginning %lf value o inter_y %lf\n", inter_x, inter_y);
		printf("HORIZONTAL: x_INC %lf and y_INC %lf with angle of: %lf\n", x_inc, y_inc, angle);
	}
	while(!wall_hit_or_out_bounds(mlx_data, inter_y, inter_x))
	{
		inter_y += y_inc;
		inter_x += x_inc;
	}
	if (mlx_data->ray->ray_n == 960)//same here checking purpose
		printf("HORIZONTAL: value of inter_x at the end %lf value o inter_y %lf\n", inter_x, inter_y);
	mlx_data->ray->h_hit_x = inter_x;//i will add this but could delete if usless
	mlx_data->ray->h_hit_y = inter_y;//same as here

	//return (fabs((inter_x - mlx_data->camera->pixel_x) * lookup_cos(angle))); //for now we keep square but this is a most efficient method
	if (mlx_data->ray->ray_n == 960)
		printf("horiz distance %lf\n",sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
	 	pow(inter_y - mlx_data->camera->pixel_y, 2)));
	
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
	 	pow(inter_y - mlx_data->camera->pixel_y, 2)));
}

float	calculate_v_inter(t_mlx_data *mlx_data, float angle)
{
	float	x_inc;
	float	y_inc;
	float	inter_x;
	float	inter_y;
	int		x_add_pixel;



	if (angle == PI / 2 || angle == 3 * PI / 2)
    	angle += 0.0001;
	y_inc = CELL_SIZE * tan(angle);

	inc_and_pixel_vert(angle, &x_inc, &x_add_pixel, &y_inc);

	inter_x = floor(mlx_data->camera->pixel_x / CELL_SIZE) * CELL_SIZE + x_add_pixel;
	inter_y = mlx_data->camera->pixel_y + (inter_x - mlx_data->camera->pixel_x) * tan(angle);

	if (mlx_data->ray->ray_n == 960)
	{
		printf("VERTICAL: value of inter_x at the beginning %lf value o inter_y %lf\n", inter_x, inter_y);
		printf("VERTICAL: x_INC %lf and y_INC %lf with angle of: %lf\n", x_inc, y_inc, angle);
	}
	while(!wall_hit_or_out_bounds(mlx_data, inter_y, inter_x))
	{
		inter_y += y_inc;
		inter_x += x_inc;
	}
	if (mlx_data->ray->ray_n == 960)
		printf("VERTICAL: value of inter_x at the end %lf value o inter_y %lf\n", inter_x, inter_y);
	mlx_data->ray->v_hit_x = inter_x;//i will add this but could delete if usless
	mlx_data->ray->v_hit_y = inter_y;//same as here
	//return (fabs((inter_y - mlx_data->camera->pixel_y) * lookup_sin(angle))); for now we keep square but this is a most efficient method
	return (sqrt(pow(inter_x - mlx_data->camera->pixel_x, 2) + \
	pow(inter_y - mlx_data->camera->pixel_y, 2)));

}

void bresenham_line(t_mlx_data *mlx_data, int x1, int y1, int x2, int y2)
{
    
	
	// if (mlx_data->ray->ray_n != SCREEN_WIDTH/2)
	// 	return ;
	// printf("coordinates received x1 %d y1 : %d, x2 %d, y2: %d ray NUMBER: %d\n", x1, y1, x2, y2, mlx_data->ray->ray_n);
	// printf("inside the bresenham algo the angle of the mid ray is: %lf\n", mlx_data->ray->current_angle * 180/PI);
	int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;  // This stays as-is because we want to move downward when y1 < y2
    int err = dx - dy;
	int p = 2 * err;

    while (1)
    {
        // Bounds checking to ensure we're within the window's dimensions
        
		if (x1 < 0 || y1 < 0 || x1 / CELL_SIZE > mlx_data->game->n_columns -1 || y1 / CELL_SIZE > mlx_data->game->n_rows -1 ||\
		 	(mlx_data->game->working_map[y1/CELL_SIZE][x1/CELL_SIZE] == '1'))
            break;

        // Plot the pixel at the current coordinates
        mlx_put_pixel(mlx_data->main_image, x1, y1, 0x00FF00FF);

        // If the end point is reached, exit the loop
        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}



void	ray_casting(t_mlx_data *mlx_data)
{
	float	h_inter_dist;
	float	v_inter_dist;
	int	which_ray;
	
	mlx_data->ray->ray_n = 0;
	mlx_data->ray->current_angle = normalize_angle(mlx_data->camera->angle - (mlx_data->camera->fov_radi / 2));
	while(mlx_data->ray->ray_n < SCREEN_WIDTH)
	{
		h_inter_dist = calculate_h_inter(mlx_data, mlx_data->ray->current_angle);
		v_inter_dist = calculate_v_inter(mlx_data, mlx_data->ray->current_angle);
		if (h_inter_dist < v_inter_dist)
		{

			mlx_data->ray->wall_dst = h_inter_dist;
			mlx_data->ray->x_final_hit = mlx_data->ray->h_hit_x;
			mlx_data->ray->y_final_hit = mlx_data->ray->h_hit_y;
		}
		else
		{
			mlx_data->ray->wall_dst = v_inter_dist;
			mlx_data->ray->x_final_hit = mlx_data->ray->v_hit_x;
			mlx_data->ray->y_final_hit = mlx_data->ray->v_hit_y;
		}
		bresenham_line(mlx_data, mlx_data->camera->pixel_x,\
		mlx_data->camera->pixel_y, mlx_data->ray->x_final_hit, mlx_data->ray->y_final_hit);
		mlx_data->ray->ray_n++;
		mlx_data->ray->current_angle = normalize_angle(mlx_data->ray->current_angle + mlx_data->camera->fov_radi / SCREEN_WIDTH); //we could also for the minipap less ray to cast, but we will see
	}
}
