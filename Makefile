# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/25 17:44:49 by qle-guen          #+#    #+#              #
#*   Updated: 2015/12/30 11:30:08 by qle-guen         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

# Directories
BINDIR	=	.
SRCDIR	=	src
OBJDIR	=	build
INCLUDE	=	include
NAME	=	ft_ls

# Compiler options
CC		=	clang
CFLAGS	=	-I$(INCLUDE) -Wall -Wextra -Werror -g


# Source files
SRC += main.c

OBJECTS=$(addprefix $(OBJDIR)/, $(subst .c,.o,$(SRC)))

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: test
test:
	@make -C test/
