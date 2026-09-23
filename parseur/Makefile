.SILENT:
NAME	= parseur.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
MAKEFLAGS += --no-print-directory

YELLOW	= \033[1;33m
RESET	= \033[0m

INCLUDES	= -I../includes -I../includes/libft

SRC		= envp_list.c istype.c expand.c \
			lexer.c lexer_lst.c lexer_cut.c lexer_op.c syntax.c \
			parseur.c parseur_cmd.c parseur_free.c
OBJ_DIR	= obj
OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	@printf "$(YELLOW)%s\n%s\n$(RESET)" "           ooooo" "          ooooooo"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
