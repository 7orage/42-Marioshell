.SILENT:
NAME	= minishell

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RFLAGS	= -lreadline
MAKEFLAGS += --no-print-directory

YELLOW	= \033[1;33m
RED		= \033[1;31m
RESET	= \033[0m

LIBFT_DIR	= includes/libft
INCLUDES	= -Iincludes -I$(LIBFT_DIR)

LIBFT		= $(LIBFT_DIR)/libft.a
UTILS		= utils/utils.a
PARSEUR		= parseur/parseur.a
SIGNALS		= signals/signals.a
BUILTINS	= builtins/builtins.a
EXEC		= exec/exec.a

# Left to right, from the most dependent to the least: the linker reads
# a static archive only once, so a user must come before its provider.
# exec -> builtins -> parseur -> signals -> utils -> libft
LIBS	= $(EXEC) $(BUILTINS) $(PARSEUR) $(SIGNALS) $(UTILS) $(LIBFT)
SUBDIRS	= $(LIBFT_DIR) utils parseur signals builtins exec

SRC		= main.c
OBJ_DIR	= obj
OBJ		= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: libs $(NAME)

libs:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir || exit 1; done

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(RFLAGS) -o $(NAME)
	@printf "$(YELLOW)%s\n%s\n%s\n$(RESET)" "      ooooooooooooooo" "      oooooo    oooooo" "     ooo           ooo"
	@printf "$(RED)%s$(RESET)\n" "    m a r i o s h e l l"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done
	rm -rf $(OBJ_DIR)

fclean:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir fclean; done
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all libs clean fclean re
