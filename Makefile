# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 02:23:03 by frey-gal          #+#    #+#              #
#    Updated: 2025/04/20 02:27:49 by frey-gal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================== VARS ==================================== #

NAME		= philosphers
CC			= cc
CFLAGS		= #-Wall -Wextra -Werror -fsanitize=address #-g

SRC			= srcs/main.c

OBJ			= $(SRC:.c=.o)

INCLUDES 	= -I.

HDR			= philosphers.h

# ================================== RULES =================================== #

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "\n==> Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

srcs/%.o: srcs/%.c $(HDR) Makefile
	@echo " -> Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "\n==> Cleaning project..."
	@rm -f $(OBJ)

fclean: clean
	@echo "\n==> Full clean..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
