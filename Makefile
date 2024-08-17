NAME = cub3D

CFLAGS = -g -Wall -Werror -Wextra -fsanitize=address

LINKS =

INCLUDES = -I./libft -I./include

SRC = main.c get_next_line.c initial_parsing.c parsing_ids_1.c \
	parsing_ids_2.c parsing_ids_3.c parsing_ids_4.c parsing_map.c \
	free_stuff.c

DIR_SRC = src

DIR_OBJ = obj

SRC := ${addprefix ${DIR_SRC}/, ${SRC}}


OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}

LIBFT = libft/libft.a

${NAME}: ${OBJ} ${LIBFT}
	${CC} -o ${CFLAGS} $^ ${LINKS} -o $@

all : ${NAME}

${LIBFT}:
	make bonus -C libft

${OBJ}: ${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	mkdir -p obj
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	rm -rf ${DIR_OBJ}

fclean: clean
	rm -rf ${NAME}
	make fclean -C libft

re: fclean all 

.PHONY: all clean fclean re
