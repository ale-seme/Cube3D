#ifndef CUBE3D_H
# define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"


typedef struct s_game
{
	char **map;
} t_game;


char	*get_next_line(int fd);

#endif
