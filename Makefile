# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: koparker <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/17 21:38:02 by koparker          #+#    #+#              #
#    Updated: 2019/03/28 16:00:07 by kfalia-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

SRC = srcs/

SOURCES = $(SRC)main.c \
		  $(SRC)ft_without_args.c \
		  $(SRC)ft_sort.c \
		  $(SRC)list.c \
		  $(SRC)argvlist.c \
		  $(SRC)ft_output_helpers.c \
          $(SRC)ft_flags.c \
		  $(SRC)ft_sort_params.c

LIBFT_FOLDER = libft

LIBFT = -L $(LIBFT_FOLDER) -lft

OBJECTS = $(SOURCES:.c=.o)

HEADERS = -I includes -I $(LIBFT_FOLDER)/includes

%.o: %.c $(INCLUDES)
	@gcc $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_FOLDER)
	@make -C $(LIBFT_FOLDER) clean
	@gcc $(FLAGS) -o $(NAME) $(HEADERS) $(OBJECTS) $(LIBFT)

all: $(NAME)

clean:
	@rm -f $(OBJECTS)
	@make -C $(LIBFT_FOLDER) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_FOLDER) fclean

re: fclean all
