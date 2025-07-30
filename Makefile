# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frey-gal <frey-gal@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 02:23:03 by frey-gal          #+#    #+#              #
#    Updated: 2025/07/30 11:55:17 by frey-gal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================== VARS ==================================== #

NAME		= philosophers
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address

SRC			= $(addprefix srcs/, helpers.c lists.c memory.c error.c \
			  parsing.c threads.c logic.c get_set.c main.c thread_utils.c \
			  monitor.c)

OBJ			= $(SRC:.c=.o)

INC 		= -I.

HDR			= philosophers.h

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
