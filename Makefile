# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 02:23:03 by frey-gal          #+#    #+#              #
#    Updated: 2025/07/17 18:16:50 by frey-gal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================== VARS ==================================== #

NAME		= philosphers
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address #-g

SRC			= $(addprefix srcs/, main.c helpers.c lists.c memory.c error.c \
			  parsing.c)

OBJ			= $(SRC:.c=.o)

INC 		= -I.

HDR			= philosphers.h

# ================================== RULES =================================== #

all: $(NAME)

# Linking
$(NAME): $(OBJ)
	@echo "\n==> Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Compiling
%.o: %.c $(HDR) Makefile
	@echo " -> Compiling $<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Cleaning
clean:
	@echo "\n==> Cleaning project..."
	@$(RM) $(OBJ)

fclean: clean
	@echo "\n==> Full clean..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
