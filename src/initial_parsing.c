#include "cub3D.h"

static void	remove_newline(char line[])
{
	int i;

	i = 0;
	while(line && line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		i++;
	}
}

static int	add_new_node(char *line, t_lst **list)
{

	t_lst *current;
	t_lst *new_node;
	
	new_node = malloc(sizeof(t_lst));
	if (!new_node)
		return(printf(ERR_NODE), 0);
	new_node->map_line = ft_strdup(line);
	if (new_node->map_line == NULL)
		return(printf(ERR_STRDUP), 0);
	new_node->next = NULL;
	if (list != NULL)
	{
		if (*list == (NULL))
			*list = new_node;
		else
		{
			current = *list;
			while((current)->next)
				current = current->next;
			current->next = new_node;
		}
	}
	return(1);
}

static int good_argument(int argc, char** argv)
{
	int	len;
	int	temp_fd;

	if (argc < 2)
		return (printf(ERR_NO_ARG), 0);
	len = ft_strlen(argv[1]);
	if (len < 4 || argv[1][len -1] != 'b' || argv[1][len -2] != 'u' || argv[1][len - 3] != 'c' || argv[1][len - 4] != '.')
		return (printf(ERR_NO_CUB), 0);
	temp_fd = open(argv[1], O_RDONLY | __O_DIRECTORY);
	if (temp_fd != -1)
		return (close(temp_fd), printf(ERR_ARG_DIR), 0);
	return (1);
	
}

int	successfull_parsing(int argc, char **argv, t_game *game)
{
	int		fd;
	char	*line;

	if (!good_argument(argc, argv))
		return(0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return(printf(ERR_ARG_OPEN), 0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		remove_newline(line);
		if (!add_new_node(line, &game->start_list_pointer))
			return (free(line), 0);
		free(line);
	}
	if (!check_ids_and_get_map_start(game->start_list_pointer, game) || \
		!check_adapt_and_copy_map(game) || !map_enclosed_by_walls(game))
		return (0);
	close(fd);
	return (1);
}
