NAME	:= cub3D
# CFLAGS	:= -Wextra -Wall/ -Werror -Wunreachable-code -O3
# CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -O3 -DDEBUG
LIBMLX	:= ./lib/mlx42
LIBGLFW := $(shell brew --prefix glfw)
LIBFT := lib/libft/libft.a

HEADERS	:= -I src/ -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT) -ldl $(LIBGLFW)/lib/libglfw3.a -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit
SRCS	:= $(shell find ./src -iname "*.c") lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c
			
OBJS	:= ${SRCS:.c=.o}
CC		:= cc

all: $(NAME)

clone_mlx42:
	@git clone --depth=1 https://github.com/codam-coding-college/MLX42.git lib/mlx42

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j6

libft:
	make -C lib/libft

%.o: %.c src/main.h 
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libmlx
