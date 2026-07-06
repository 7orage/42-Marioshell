.SILENT:
NAME    = parcing

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g3

LIBFT_DIR   = ../includes/libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRC     = main.c istype.c lexer.c parceur.c print_ast.c envp_list.c
OBJ_DIR = obj
OBJ     = $(SRC:%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I. -I$(LIBFT_DIR)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re