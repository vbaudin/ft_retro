# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrajaona <mrajaona@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/02 09:35:30 by mrajaona          #+#    #+#              #
#    Updated: 2018/06/02 14:37:03 by vbaudin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_retro

DIRSRC		=	./src/
SRC			=	AEnemy.class.cpp \
				AEntity.class.cpp \
				Bullet.class.cpp \
				IShip.class.cpp \
				Player.class.cpp \
				Minion.class.cpp \
				main.cpp \
				Map.cpp \
				Game.cpp \
				Star.class.cpp


DIRINC		=	./inc/
INC			=	AEnemy.class.hpp \
				AEntity.class.hpp \
				Bullet.class.hpp \
				IShip.class.hpp \
				Player.class.hpp \
				Minion.class.hpp \
				error.hpp

SRCS		=	$(addprefix $(DIRSRC), $(SRC))
INCS		=	$(addprefix $(DIRINC), $(INC))
OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-Wall -Wextra -Werror -I$(DIRINC)

CC			=	/usr/bin/clang++
RM			=	/bin/rm -rf
ECHO		=	/usr/bin/printf

all		:	$(NAME)

.cpp.o	:
			$(CC) -c $(CPPFLAGS) -o $@ $<

$(OBJS)	:	$(INCS)

$(NAME)	:	$(OBJS)
			$(CC) $(CPPFLAGS) $(OBJS) -lncurses -o $@
			@$(ECHO) "[32m> Executable compiled[0m\n"

clean	:
			@$(RM) $(OBJS)
			@$(ECHO) "[31m> Directory cleaned[0m\n"

fclean	:	clean
			@$(RM) $(NAME)
			@$(ECHO) "[31m> Removed executable[0m\n"

re		:	fclean all

.PHONY	:	all clean fclean re

.DEFAULT_GOAL	:=	all
