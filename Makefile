# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valarcon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 11:46:40 by valarcon          #+#    #+#              #
#    Updated: 2022/12/12 17:44:25 by valarcon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS =  src/main.c\
        src/philo.c\
        src/init.c\
        src/utils.c\
		src/utils2.c\
        src/binding.c\

OBJS = $(SRCS:.c=.o)

$(NAME) :
	gcc $(CFLAGS) $(SRCS) -o $(NAME)
all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	 $(RM) $(OBJS)

re : fclean all
