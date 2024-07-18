#ifndef CUBE3D_H
# define CUBE3D_H

#include <unistd.h>
#include <stdio.h>
#include "libft.h"


typedef struct s_lst
{
	char 			*map_line;
	struct s_lst 	*next;
} t_lst;


char	*get_next_line(int fd);

#endif
