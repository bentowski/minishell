SHELL :=		/bin/bash

NAME =			minishell
CC =			clang -D BUFFER_SIZE=4 -g
FLAGS =			-Wall -Wextra -Werror
RM =			rm -rf
DIR_SRCS =		./
LINUX_FLAGS =	-lXext -lX11 -lm
LIBMLX =		libmlx.a
LIBFT =			libft.a
SRC =	main.c \
		ft_free.c \
		errors.c \
		gestion_cmds.c \
		cmd_part_one.c \
		pipes.c	\
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))
OBJS =			$(SRCS:.c=.o)
COMPIL = $(FLAGS) $(OBJS) $(LINUX_FLAGS) -L $(LIB)libft -lft -o

all:			$(NAME)
				@echo "Compiled "$(NAME)" successfully!"

$(NAME) :		$(OBJS)
				@$(MAKE) -C ./libft bonus
				@cp ./libft/libft.a libft.a
				@$(CC) $(COMPIL) $(NAME)

%.o: %.c
				@$(CC) -c $< -o $@
				@echo "Compiled "$<" successfully!"

clean:
	$(MAKE) -C ./libft clean
	$(RM) *.o */*.o

fclean: clean
	$(MAKE) -C ./libft fclean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all
