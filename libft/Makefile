NAME = libft.a

FLAGS = -Wall -Wextra -Werror

HEADER = include

DIR_O = ft_strcpy.c \
		ft_split.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strlen.c \
		ft_strjoin.c \
		ft_strdup.c \

OBJS = ${addprefix srcs/,${DIR_O:.c=.o}}

CC = clang

.c.o:
	${CC} ${FLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS} ${HEADER}
	ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re