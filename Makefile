# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbillon <tbillon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 09:27:55 by tbillon           #+#    #+#              #
#    Updated: 2022/05/23 15:42:30 by tbillon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREY        =   \033[30m
RED         =   \033[31m
GREEN       =   \033[32m
YELLOW      =   \033[33m
BLUE        =   \033[34m
PINK        =   \033[35m
CYAN        =   \033[36m
WHITE       =   \033[37m
BOLD        =   \033[1m
UNDER       =   \033[4m
SUR         =   \033[7m
END         =   \033[0m

NAME 		=	ft_containers

RM			= 	rm -rf

CC 			= 	clang++ -std=c++98

FLAGS		= 	-Wall -Werror -Wextra

MEMCHECK 	= 	-g

INCS		= 	includes/containers/vector.hpp \
				includes/containers/map.hpp \
				includes/containers/stack.hpp \
				includes/iterators/iterator_traits.hpp \
				includes/iterators/reverse_iterator.hpp \
				includes/iterators/random_access_iterator.hpp \
				includes/iterators/tree_iterator.hpp \
				includes/utils/enable_if.hpp\
				includes/utils/is_integral.hpp\
				includes/utils/equal.hpp\
				includes/utils/lexicographical_compare.hpp\
				includes/utils/pair.hpp\
				includes/utils/tree.hpp


SRCS 		= 	main.cpp

OBJS 		= 	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) $(MEMCHECK) -o $(NAME)

%.o:		%.cpp $(INCS)
			$(CC) $(FLAGS) -c $< -o $@ -I 

clean:
			@$(RM) *.o
			@$(RM) mytests/*.o
			@printf "$(ERASE)$(RED)-> All files *.o cleaned$(END)\n"

fclean:		clean
			@$(RM) ft_containers
			@$(RM) ft_containers.dSYM
			@printf "$(ERASE)$(RED)-> Executable cleaned$(END)\n"

re: 		fclean all

.PHONY: 	all fclean clean re
