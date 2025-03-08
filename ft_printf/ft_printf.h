/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:45:16 by maximemarti       #+#    #+#             */
/*   Updated: 2024/10/12 15:09:43 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_printf
{
	char	symbol;
	int		(*f)(va_list *);
}	t_printf;
int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_print_s(va_list *ptr);
int		ft_print_c(va_list *ptr);
int		ft_print_i(va_list *ptr);
int		ft_print_ui(va_list *ptr);
int		ft_print_x(va_list *ptr);
int		ft_print_bx(va_list *ptr);
int		print_ptr(va_list *ptr);

#endif
