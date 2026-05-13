
.SILENT:
NAME = minishell

SRC = main.c 
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RFLAGS = -lreadline
MAKEFLAGS += --no-print-directory


LIBFT_DIR = includes/libft
FT_PRINTF_DIR = includes/ft_printf
NEXT_LINE_DIR   = includes/get_next_line

LIBFT     = $(LIBFT_DIR)/libft.a
FT_PRINTF       = $(FT_PRINTF_DIR)/libftprintf.a
NEXT_LINE	= $(NEXT_LINE_DIR)/get_next_line.a


all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR) --no-print-directory

$(NEXT_LINE):
	@make -C $(NEXT_LINE_DIR) --no-print-directory


$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(NEXT_LINE)
	@$(CC) $(CFLAGS) $(RFLAGS) $(OBJ) $(FT_PRINTF) $(NEXT_LINE) $(LIBFT) -o $(NAME)
	@echo "*******************"
	@echo "  PROJET COMPILE   "
	@echo "*******************"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(RFLAGS) -I. -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(NEXT_LINE_DIR) -c $< -o $@


clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@make -C $(NEXT_LINE_DIR) clean
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	@make -C $(NEXT_LINE_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re