SHELL :=		/bin/bash

NAME =			minishell
CC =			clang -D BUFFER_SIZE=4 -g
FLAGS =			-Wall -Wextra -Werror
RM =			rm -rf
DIR_SRCS =		./
LIBFT =			libft.a
LIBFT_DIR = 	./includes/libft
READLINE_DIR =  ./includes/readline-8.1
SRC =	srcs/main.c \
		srcs/parsing/parsing.c \
		srcs/parsing/heredoc.c \
		srcs/parsing/vars_gestion.c \
		srcs/parsing/add_space.c \
		srcs/parsing/add_space2.c \
		srcs/parsing/cmd_line_utils.c\
		srcs/parsing/token_utils.c\
		srcs/errors/errors.c \
		srcs/exec/gestion_cmds.c \
		srcs/exec/ft_pwd.c \
		srcs/exec/ft_cd.c \
		srcs/exec/cmd_part_one.c \
		srcs/exec/custom_split.c\
		srcs/exec/pipes.c \
		srcs/utils/ft_clear.c \
		srcs/utils/array_size.c \
		srcs/utils/utils.c \
		srcs/utils/env.c \
		srcs/utils/signals.c

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))
OBJS =			$(SRCS:.c=.o)
LIBS_COMPIL =  -lreadline -lncurses -lft -o
COMPIL = $(FLAGS) $(OBJS) -L $(LIBFT_DIR) -L $(READLINE_DIR) $(LIBS_COMPIL)

all:			$(NAME)
				@echo "Compiled "$(NAME)" successfully!"

$(NAME) :		$(OBJS)
				@$(MAKE) -C $(LIBFT_DIR) bonus
				@cp $(LIBFT_DIR)/libft.a libft.a
				# @cd $(READLINE_DIR) && ./configure && cd ../..
				$(MAKE) -C $(READLINE_DIR)
				@$(CC) $(FLAGS) $(COMPIL) $(NAME)

%.o: %.c
				@$(CC) $(FLAGS) -c $< -o $@
				@echo "Compiled "$<" successfully!"

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(READLINE_DIR) clean
	$(RM) *.o srcs/*.o srcs/*/*.o

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all
