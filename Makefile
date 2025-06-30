NAME        = cube3d

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_PATH) -I$(LIBFT_PATH)/includes -g
LDFLAGS     = -L$(MLX_PATH) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lbsd -L$(LIBFT_PATH) -lft

LIBFT_PATH  = ./libft
MLX_PATH    = ./minilibx-linux

SRC_DIR     = ./srcs
GNL_DIR     = ./gnl
PARSING_DIR = ./parsing
INC_DIR     = ./includes

MAIN_SRCS   = $(SRC_DIR)/main.c \
			  $(SRC_DIR)/exit_error.c \
			  $(SRC_DIR)/draw.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/movements.c \
			  $(SRC_DIR)/ray.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/textures.c

GNL_SRCS    = $(GNL_DIR)/get_next_line.c \
              $(GNL_DIR)/get_next_line_utils.c

SRCS        = $(MAIN_SRCS) $(GNL_SRCS) $(PARSING_SRCS)

OBJS        = $(SRCS:.c=.o)
LIBFT       = $(LIBFT_PATH)/libft.a
MLX         = $(MLX_PATH)/libmlx_Linux.a

GREEN       = \033[1;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
RED         = \033[0;31m
RESET       = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_PATH) --no-print-directory

$(MLX):
	@echo "$(YELLOW)Compiling minilibx...$(RESET)"
	@make -C $(MLX_PATH) --no-print-directory

%.o: %.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_PATH) --no-print-directory
	@make clean -C $(MLX_PATH) --no-print-directory 2>/dev/null || true
	@echo "$(GREEN)Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH) --no-print-directory
	@echo "$(GREEN)$(NAME) cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re