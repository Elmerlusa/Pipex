# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 15:10:27 by javmarti          #+#    #+#              #
#    Updated: 2022/11/11 15:10:27 by javmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LFTPATH = ./srcs/Libft/
CFILESLFT = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

PTFPATH = ./srcs/Printf/
CFILESPTF = ft_printf.c ft_printchar.c ft_printhex.c ft_printint.c ft_printptr.c \
		ft_printstr.c ft_printuint.c

GNLPATH = ./srcs/GetNextLine/
CFILESGNL = get_next_line.c

SRCS = ${addprefix ${LFTPATH}, ${CFILESLFT}} \
		${addprefix ${PTFPATH}, ${CFILESPTF}} \
		${addprefix ${GNLPATH}, ${CFILESGNL}}

OBJS = ${SRCS:.c=.o}
INCS = -I ./includes/

LIB = libft.a

RM = rm -rf
################################################################################
.PHONY: all re fclean clean
################################################################################
all:		${LIB}

${LIB}:		${OBJS}
		@ar rcs ${LIB} ${OBJS}

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INCS}

re:			fclean all

fclean:		clean
		@${RM} ${LIB}

clean:
		@${RM} ${OBJS}
################################################################################
