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
CFILES = 

SRCS = ${addprefix ${SRCSDIR}, ${CFILES}}

OBJS = ${SRCS:.c=.o}

INC = -I ./includes/ -I ./libft/includes/

NAME = pipex

LIB = libft.a
LIBDIR = ./libft/

RM = rm -rf
################################################################################
.PHONY: test
################################################################################
test:
		make -s ${LIB}
		${CC} ${CFLAGS} test.c -o ${NAME} -I ./libft/includes -I ./includes -L ${LIBDIR} -l ft
		./${NAME}

${LIB}:
		make -s -C ${LIBDIR}