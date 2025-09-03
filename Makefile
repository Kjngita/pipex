NAME = pipex
CFILES = main.c command.c cleanup.c
O_DIR = objdir
OFILES = $(addprefix $(O_DIR)/,$(CFILES:.c=.o))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FLAGS = -Wall -Wextra -Werror -g
HEADER = header_pipex.h

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OFILES) $(LIBFT)
	cc $(FLAGS) $(OFILES) $(LIBFT) -o $(NAME)
	@echo "\033[33m** Program created **\033[0m"

$(O_DIR):
	mkdir -p $@

$(O_DIR)/%.o: %.c $(HEADER) | $(O_DIR)
	cc $(FLAGS) -c $< -o $@ -I$(LIBFT_DIR)

clean:
	rm -rf $(O_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	@echo "\033[33m** Object files deleted **\033[0m"

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "\033[33m** Program deleted **\033[0m"

re: fclean all

.SECONDARY: $(OFILES)

.PHONY: all clean fclean re

.SILENT: