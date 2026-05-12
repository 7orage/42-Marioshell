
.SILENT:
NAME = minishell

SRC = main.c 
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(RFLAGS) $(OBJ) -o $(NAME)
	@echo "*******************"
	@echo "  SERVER COMPILE   "
	@echo "*******************"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(RFLAGS) -I. -c $< -o $@


clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re