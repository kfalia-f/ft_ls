# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: koparker <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/21 17:39:07 by koparker          #+#    #+#              #
#    Updated: 2019/04/28 18:02:36 by koparker         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

WFLAGS = -Wall -Wextra -Werror

NAME = libft.a

HDR = -I includes

SRC = ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
	  ft_listsize.c ft_lstpush_back.c ft_lstback.c ft_lstat.c \
	  ft_lstinsert_at.c ft_lstfree_node.c \
	  ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	  ft_strlen.c ft_2d_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c \
	  ft_strchr.c ft_strrchr.c ft_strnchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c \
	  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	  ft_putchar_base.c ft_putstr_base.c ft_putnbr_base.c ft_strrev.c ft_memcpy_backwards.c \
	  ft_memalloc.c ft_memalloc_2d_clean.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
	  ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strjoinre.c ft_strtrim.c \
	  ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c  get_next_line.c \
	  ft_str_path.c ft_ls_path_to_file.c ft_del.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

.c.o:
	@gcc -c $(WFLAGS) $(HDR) $? -o $@

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
