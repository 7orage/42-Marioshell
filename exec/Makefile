.SILENT:
NAME	= exec.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
MAKEFLAGS += --no-print-directory

YELLOW	= \033[1;33m
RESET	= \033[0m

INCLUDES	= -I../includes -I../includes/libft

SRC		= exec.c exec_cmd.c exec_red.c \
			exec_path.c exec_utils.c heredoc.c
OBJ_DIR	= obj
OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	@printf "$(YELLOW)%s\n%s\n$(RESET)" "       ooooooooooooo" "      ooooooooooooooo"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
