/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:48:12 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/27 18:48:12 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define STDOUT 1

int	ft_printf(char const *str, ...);
int	ft_printchar(char c);
int	ft_printhex(unsigned int n, char c);
int	ft_printint(int n);
int	ft_printptr(void *ptr);
int	ft_printstr(char const *str);
int	ft_printuint(unsigned int n);

#endif