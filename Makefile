NAME		=	ft_ls
SRCSDIR		=	srcs
OBJSDIR		=	objs
B_SRCSDIR	=	srcs_bonus
INCLUDES	=	includes

SRCS		=	main.c init.c setup_opts.c setup_paths.c setup_dir_stats.c clean_all.c output.c

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INCLUDES) -I$(LIBFT_DIR)

OBJS		= $(SRCS:%.c=$(OBJSDIR)/%.o)

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -o $(NAME) -g
	@echo "Done!"

# Compilando cada objeto e incluindo o diretório da libft
$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -g

$(LIBFT):
	@ $(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
