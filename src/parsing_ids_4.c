#include "cub3D.h"

static int	check_and_atoi(char *str)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	if (!str)
		return (0);
	while((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (!str[i])
		return(printf("Error: one of the rbgs is empty or contains only spaces\n"), -1);
	while(str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			printf("only digit after spaces as RBG codes\n");
			return (-1);
		}
		if (number > (255 - (number + str[i] - '0')) / 10)
		{
			printf("number given as RBG parameter should be max 255\n");
			return (-1);
		}
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number);
}

static int	traverse_and_atoi_check(int n_id, t_game *game, char **ss)
{
	int i;
	int *array;
	
	i = -1;
	array = malloc(sizeof(int) * 3);
	if (!array)
		return (printf("Error: failed to malloc the int array for RGBs\n"), 0);
	if (n_id == 4)
		game->floor_rbg_array = array;
	else
		game->cealing_rbg_array = array;
	while(ss[++i])
	{
		
		array[i] = check_and_atoi(ss[i]);
		if (array[i] < 0)
			return (0);
	}
	return (1);
}

static int	right_amount(char **ss)
{
	int	i;
	
	i = 0;
	while(ss[i])
	{
		i++;
	}
	return (i == 3);
}

int	split_store_and_check_rbg_amount(char *temp, int n_id, t_game *game)
{
	char **ss;

	ss = ft_split(temp, ',');
	if (!ss)
		return (printf("Error in splitting the rgb values for the identifier\n"), 0);
	if (!right_amount(ss))//need also here to free the goddamn thing array
		return (free_split(ss), printf("Error: the program accepts 3 and only 3 RGBs for the ids\n"), 0);
	if (!traverse_and_atoi_check(n_id, game, ss))
		return (free_split(ss), 0);
	free_split(ss);
	return (1);
}