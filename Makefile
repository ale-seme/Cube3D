NAME = cub3D

CFLAGS = -g -Wall -Werror -Wextra

LINKS =

INCLUDES = -I./libft -I./include

SRC = test.c main.c get_next_line.c check_identifiers.c map_management.c

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
