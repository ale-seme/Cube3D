#ifndef CUBE3D_H
# define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"


#define CARDINALS "NSWE"
#define ELEMENTS "01"
// typedef struct game_info
// {
// 	int rbgs[2][3];

// 	char **floor_rbg;
// 	char **ceiling_rbg;

	
// }

typedef struct s_lst
{
	char			*map_line;
	struct s_lst 	*next;
} t_lst;

typedef struct s_camera
{
	int		x;
	int		y;
	char	cardinal_point;
} t_camera;

typedef struct s_game
{
	t_lst			*start_list_pointer;
	t_lst			*start_map_pointer;
	t_camera		*camera_start_info;
	char			*texture_nord;
	char			*texture_south;
	char			*texture_west;
	char			*texture_east;
	char			**floor_rbg;
	char			**cealing_rbg;

	
} t_game;

typedef struct s_count
{
	int	count_nord;
	int	count_south;
	int	count_west;
	int	count_east;
	int	count_floor;
	int	count_ceiling;
}	t_count;



char	*get_next_line(int fd);

#endif
