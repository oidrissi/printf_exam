#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct s_flags
{
	int	width;
	int	precision;
	int dot;
	int count;
}	t_flags;

void	init_flags(t_flags flags)
{
	flags.width = 0;
	flags.precision = 0;
	flags.dot = 0;
}

int		count_ints(long num, int base)
{
	int i = 1;
	if (num >= base)
	{
		num = num / base;
		i++;
	}
	return (i);
}

int		ft_strlen(char *str)
{
	int i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void    ft_putchar(char c, t_flags p)
{
        write(1, &c, 1);
        p.count++;
}

void	ft_putnbr(long int nb, t_flags flags)
{
	if (nb < 0)
	{
		ft_putchar('-', flags);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10, flags);
		ft_putnbr(nb % 10, flags);
	}
	else 
		ft_putchar(nb + '0', flags);
}

void	treat_d(t_flags flags, va_list ag)
{
	long f;
	int size;
	int pad;
	
	f = va_arg(ag, int);
	size = count_ints(f, 10);
	if (flags.width > size)
	{
		pad = flags.width - size;
		while (pad > 0)
		{
			write(1, " ", 1);
			pad--;
		}
	}
	ft_putnbr(f, flags);
}

void	parse_flags(va_list ag, t_flags flags, const char *str)
{
	int i = 0; int res = 0;

	while (str[i])
	{
		if (isdigit(str[i]))
		{
			flags.width = atoi(&str[i]);
			i++;
		}
		if (str[i] == '.' && isdigit(str[i + 1]))
		{
			flags.dot = 1;
			i++;
		}
		if (flags.dot)
		{
			if (isdigit(str[i]))
			{
				flags.precision = atoi(&str[i]);
				i++;
			}
		}
		if (str[i] == 'd')
			treat_d(flags, ag);
		break;
		// else if (str[i] == 's')
		// 	treat_d(str, flags, ag);
		// else if (str[i] == 'x')
		// 	treat_d(str, flags, ag);
	}
}

void	ft_printf_aux(const char *str, va_list ag, t_flags flags)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '%')
		{
			write(1, str, 1);
			i++;
		}
		else if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				break;
			i++;
			parse_flags(ag, flags, str + i);
		}
		break;
	}
}

int ft_printf(const char *str, ...)
{
    va_list ag;
	t_flags flags;

	p_size = 0;
	init_flags(flags);
    va_start(ag, str);
	ft_printf_aux(str, ag, flags);
	va_end(ag);
	return (flags.count);
}

int main()
{
	ft_printf("%3d\n", 15);
	// printf("%12d", 15);
	return (0);
}