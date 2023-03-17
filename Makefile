# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 15:40:07 by javmarti          #+#    #+#              #
#    Updated: 2022/11/30 15:40:07 by javmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCSDIR = ./srcs/
CFILES = pipex.c utils.c parse_input.c childs.c

SRCS = ${addprefix ${SRCSDIR}, ${CFILES}}

OBJS = ${SRCS:.c=.o}

INC = -I ./includes/ -I ./libft/includes/

NAME = pipex

LIB = libft.a
LIBDIR = ./libft/

RM = rm -rf

CMD1 = ls -lA
CMD2 = 
################################################################################
.PHONY: all test test_hdoc test_many test_error re fclean clean
################################################################################
all:		${NAME}

test:		${NAME}
		./${NAME} hola.txt "/usr/bin/ls -lA" "/usr/bin/grep git" adios.txt && cat adios.txt
		./${NAME} hola.txt "ls -lA" "grep git" adios.txt && cat adios.txt
		< hola.txt ls -lA | grep git

test_hdoc:	${NAME}
		./${NAME} here_doc exit "tr a-z A-Z" "wc -l" adios.txt && cat adios.txt

test_many:	${NAME}
		./${NAME} hola.txt "ls -lA" "grep git" "wc -w" "cat -e" adios.txt && cat adios.txt
		< hola.txt ls -lA | grep git | wc -w | cat -e

error:		${NAME}
		./${NAME} oads "ul -e" "wc -l" adios.txt
		@echo "---------------------------------------------------------"
		./${NAME} hola.txt "ula -e" "wcx -l" adios.txt
		@echo "---------------------------------------------------------"
		./${NAME} hola.txt "ula -e" adios.txt "wcx -l"
		@echo "---------------------------------------------------------"

${NAME}:	${OBJS}
		@make -s ${LIB}
		@${CC} $^ -L ${LIBDIR} -l ft -o ${NAME}

${LIB}:
		@make -s -C ${LIBDIR}

%.o:		%.c
		@${CC} -c ${CFLAGS} $^ -o $@ ${INC}

re:			fclean all

fclean:		clean
		@make -s -C ${LIBDIR} fclean
		@${RM} ${NAME}

clean:
		@make -s -C ${LIBDIR} clean
		@${RM} ${OBJS}
################################################################################