/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:30:55 by mneri             #+#    #+#             */
/*   Updated: 2022/10/18 10:30:56 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include "Libft/libft.h"
# include <stdio.h>

typedef struct state
{
	int	count;
	int	state;
}	t_state;

int				ft_printf(const char *format, ...);
unsigned int	ft_putlowhex(unsigned int n);
unsigned int	ft_putuphex(unsigned int n);
unsigned int	ft_putuinptr(uintptr_t n);
int				ft_countdigits(long long int n);
int				ft_p(const char*s, const void *l);
uintptr_t		ft_countptrhex(uintptr_t n );
unsigned int	ft_counthexdig(unsigned int n);
void			ft_putunsignednbr(unsigned int n, int fd);
char			*ft_print_cs(char *format, va_list args, t_state *state);
char			*ft_print_diu(char *format, va_list args, t_state *state);
char			*ft_print_x(char *format, va_list args, t_state *state);
char			*ft_print_ptr_cent(char *format, va_list args, t_state *state);
char			*ft_printstate1(char *c, va_list args, t_state *state);
char			*ft_hpx(int temp, uintptr_t n, char *str, uintptr_t len);
char			*ft_hlx(unsigned int temp, unsigned int n, char *str, int len);
char			*ft_hux(unsigned int temp, unsigned int n, char *str, int len);
char			*ft_print_ptr(char *format, va_list args, t_state *state);
char			*ft_print_pcent(char *format, va_list args, t_state *state);
void			ft_printstate0(char *c, t_state *state);
char			*ft_print_hash(char *format, va_list args, t_state *state);
char			*ft_print_space(char *format, va_list args, t_state *state);
char			*ft_print_plus(char *format, va_list args, t_state *state);

#endif
