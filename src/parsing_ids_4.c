

#include "cub3D.h"

static int	check_and_atoi(char *str)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (!str[i])
		return (printf(ERR_NO_RBG), -1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (printf(ERR_BAD_RBG), -1);
		if (number > (255 - (str[i] - '0')) / 10)
			return (printf(ERR_OVFL_RBG), -1);
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number);
}

static int	traverse_and_atoi_check(int n_id, t_game *game, char **ss)
{
	int	i;
	int	*array;

	i = -1;
	array = malloc(sizeof(int) * 3);
	if (!array)
		return (printf(ERR_ARRAY), 0);
	if (n_id == 4)
		game->floor_rbg_array = array;
	else
		game->cealing_rbg_array = array;
	while (ss[++i])
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
	while (ss[i])
	{
		i++;
	}
	return (i == 3);
}

int	split_store_and_check_rbg_amount(char *temp, int n_id, t_game *game)
{
	char	**ss;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (temp && temp[i])
	{
		if (temp[i++] == ',')
			count++;
	}
	if (count != 2)
		return (printf(ERR_SPL_COUNT), 0);
	ss = ft_split(temp, ',');
	if (!ss)
		return (printf(ERR_SPL_RBG), 0);
	if (!right_amount(ss))
		return (free_split(ss), printf(ERR_NUM_RGBS), 0);
	if (!traverse_and_atoi_check(n_id, game, ss))
		return (free_split(ss), 0);
	free_split(ss);
	return (1);
}
