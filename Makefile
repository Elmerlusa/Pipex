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
CFILES = pipex.c utils.c childs.c

SRCS = ${addprefix ${SRCSDIR}, ${CFILES}}

OBJS = ${SRCS:.c=.o}

INC = -I ./includes/ -I ./libft/includes/

NAME = pipex

LIB = libft.a
LIBDIR = ./libft/

RM = rm -rf

CMD1 = ls -l -A
CMD2 = grep git
################################################################################
.PHONY: test
################################################################################
all:		${NAME}

test:		${NAME}
		./${NAME} hola.txt "${CMD1}" "${CMD2}" adios.txt && cat adios.txt
		< hola.txt ${CMD1} | ${CMD2}

test_hdoc:	${NAME}
		./${NAME} here_doc exit "tr a-z A-Z" "wc -l" adios.txt && cat adios.txt
		tr a-z A-Z << cat | wc -l


error:		${NAME}
		./${NAME} hola.txt "ul -e" "wc -l" adios.txt && cat adios.txt
		< hola.txt ul -e | wc -l
		@echo "---------------------------------------------------------"
		./${NAME} hola.txt "ula -e" "wc -l" adios.txt && cat adios.txt
		< hola.txt ula -e | wc -l
		@echo "---------------------------------------------------------"
		./${NAME} hola.txte "ula -e" "wc -l" adios.txt && cat adios.txt
		< hola.txte ula -e | wc -l
		@echo "---------------------------------------------------------"
		./${NAME} hola "ls -e" "wc -l" adios.txt && cat adios.txt
		< hola ls -e | wc -l

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