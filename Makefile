NAME = pipex
CFILES = 
O_DIR = objdir
OFILES = $(addprefix $(O_DIR)/,$(CFILES:.c=.o))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FLAGS = -Wall -Wextra -Werror
HEADER = header_pipex.h

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OFILES)
	cc $(FLAGS) $(OFILES) $(LIBFT) -o $(NAME)

$(O_DIR):
	mkdir -p $@

$(O_DIR)/%.o: %.c $(HEADER) | $(O_DIR)
	cc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(O_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SILENT:

.PHONY: all clean fclean re