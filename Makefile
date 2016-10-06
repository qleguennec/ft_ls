# Directories
PROJECT		=	ft_ls
BINDIR		?=	.
BUILDDIR	?=	build
NAME		=	$(BINDIR)/ft_ls

# Compiler options
CC			=	clang
CFLAGS		=	$(addprefix -I,$(INCLUDE)) -Wall -Wextra -Werror -g

# Color output
BLACK		=	"\033[0;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
BLUE		=	"\033[0;34m"
MAGENTA		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[0;37m"
END			=	"\033[0m"

SRC += fmt_l.c
SRC += ft_ls.c
SRC += ls_exit.c
SRC += main.c
SRC += sort_lex.c
SRC += sort_quicksort.c
SRC += util.c

LIB += libprintf.a
LIB += libvect.a
LIB += libft.a

OBJECTS		=	$(addprefix $(BUILDDIR)/, $(SRC:%.c=%.o))
LIBRARIES	=	$(addprefix $(BUILDDIR)/, $(LIB)) $(MLX)
LIBLINK		+=	$(addprefix -l, $(LIB:lib%.a=%))

all: $(NAME)

$(MLX): $(MLXDIR)
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	make -C $(MLXDIR)

$(BUILDDIR)/%.a: %
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	BINDIR=$(CURDIR)/$(BUILDDIR) BUILDDIR=$(CURDIR)/$(BUILDDIR) \
		   make --no-print-directory -C $<

$(BUILDDIR)/%.o: %.c
	@[ -d $(BUILDDIR) ] || mkdir $(BUILDDIR)
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIBRARIES)
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	@$(CC) $(CFLAGS) -L$(BUILDDIR) $(LIBLINK) $(OBJECTS) $(LIBLINK) -o $(NAME)
	@echo "OK\t"$(NAME)

.PHONY: clean fclean re

clean:
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	rm -rf $(OBJECTS)

fclean: clean
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	rm -rf $(BUILDDIR)
	rm -rf $(NAME)

re: fclean all
