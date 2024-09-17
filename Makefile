# Colors
GREEN=\033[1;32m
RED=\033[0;31m
BLUE=\033[1;34m
PURPLE=\033[1;35m
END=\033[0m

.SILENT:

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include/
RM = rm -rf

LIBFT = libft.a
LIBPATH = lib

NAME = fdf
SRC_FILES = main.c map.c draw.c utils.c
SRC_DIR = ./src/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)

MLXFLAGS = -lmlx -I./minilibx-linux -L./minilibx-linux -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBPATH) --no-print-directory
	$(CC) $(CFLAGS) $(OBJ) $(LIBPATH)/$(LIBFT) -o $(NAME) $(MLXFLAGS)
	echo "$(PURPLE)Fdf ready !$(END)"

clean:
	make clean -C $(LIBPATH) --no-print-directory
	$(RM) $(OBJ)

fclean: clean
	make fclean -C $(LIBPATH) --no-print-directory
	$(RM) $(NAME)

re: fclean all

debug: $(OBJ)
	make -C $(LIBPATH) --no-print-directory
	$(CC) $(CFLAGS) -g $(OBJ) $(LIBPATH)/$(LIBFT) -o $(NAME) $(MLXFLAGS)

.PHONY: all clean fclean re