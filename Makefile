# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: koparker <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/17 21:38:02 by koparker          #+#    #+#              #
#    Updated: 2019/04/22 17:39:34 by koparker         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

SRC = srcs/

SOURCES = $(SRC)main.c \
		  $(SRC)ft_sort.c \
		  $(SRC)list.c \
		  $(SRC)ft_output_helpers.c \
          $(SRC)ft_flags.c \
		  $(SRC)ft_sort_params.c \
		  $(SRC)ft_with_args.c \
		  $(SRC)ft_sort_balancer.c \
		  $(SRC)ft_recursion_flag.c \
		  $(SRC)ft_l_flag.c \
		  $(SRC)ft_print.c \
		  $(SRC)ft_lstname_to_char_arr.c \
		  $(SRC)ft_cmp.c \
		  $(SRC)ft_current_dir.c \
		  $(SRC)prepare_args.c \
		  $(SRC)ft_l_helper.c \
		  $(SRC)ft_l_get_info.c \
		  $(SRC)ft_l_output.c \
		  $(SRC)G_flag.c

LIBFT_FOLDER = libft

LIBFT = -L $(LIBFT_FOLDER) -lft

OBJECTS = $(SOURCES:.c=.o)

HEADERS = -I includes -I $(LIBFT_FOLDER)/includes

%.o: %.c $(INCLUDES)
	@gcc -g $(FLAGS) $(HEADERS) -c $< -o $@

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
