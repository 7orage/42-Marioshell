.SILENT:
NAME	= builtins.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
MAKEFLAGS += --no-print-directory

YELLOW	= \033[1;33m
RESET	= \033[0m

INCLUDES	= -I../includes -I../includes/libft

SRC		= dispatch.c env_edit.c \
			ft_echo.c ft_pwd.c ft_env.c ft_cd.c \
			ft_export.c export_print.c ft_unset.c ft_exit.c
OBJ_DIR	= obj
OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	@printf "$(YELLOW)%s\n%s\n$(RESET)" "  oooooooo  ooo  oooooooo" "     ooooooooooooooooo"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
