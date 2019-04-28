# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/17 21:38:02 by koparker          #+#    #+#              #
#    Updated: 2019/04/28 15:49:30 by kfalia-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

SRC = srcs/

SOURCES = $(SRC)main.c \
		  $(SRC)ft_sort.c \
		  $(SRC)list.c \
		  $(SRC)list_helpers.c \
		  $(SRC)ft_output_helpers.c \
          $(SRC)ft_flags.c \
		  $(SRC)ft_with_args.c \
		  $(SRC)ft_sort_balancer.c \
		  $(SRC)ft_recursion_flag.c \
		  $(SRC)ft_l_flag.c \
		  $(SRC)print.c \
		  $(SRC)print_colorized.c \
		  $(SRC)ft_lstcontent_to_char_arr.c \
		  $(SRC)ft_cmp.c \
		  $(SRC)ft_current_dir.c \
		  $(SRC)prepare_args.c \
		  $(SRC)ft_l_helper.c \
		  $(SRC)ft_l_get_info.c \
		  $(SRC)ft_l_output.c \
		  $(SRC)upper_g_flag_l.c \
		  $(SRC)upper_g_flag.c \
		  $(SRC)ft_recursion_helpers.c

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

test:
	@gcc -g $(FLAGS) -o $(NAME) $(HEADERS) $(SOURCES) $(LIBFT)
