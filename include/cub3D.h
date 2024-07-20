#ifndef CUBE3D_H
# define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

// typedef struct game_info
// {
// 	int rbgs[2][3];

// 	char **floor_rbg;
// 	char **ceiling_rbg;

	
// }

typedef struct s_count
{
	int	count_nord;
	int	count_south;
	int	count_west;
	int	count_east;
	int	count_floor;
	int	count_ceiling;
}	t_count;

typedef struct s_lst
{
	char 			*map_line;
	struct s_lst 	*next;
} t_lst;


char	*get_next_line(int fd);

#endif
