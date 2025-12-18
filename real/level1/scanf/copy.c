#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	char	c;
	
	while ((c = fgetc(f)) != EOF) {
		if (!isspace(c)) {
			ungetc(c, f);
			return (0);
		}
	}
	if (ferror(f))
		return (-1);
	return (0);
}

int match_char(FILE *f, char c)
{
	char	c_read = fgetc(f);
	if (c_read == EOF) {
		if(ferror(f))
			return (-1);
		return (0);
	}
	if (c_read == c)
		return (1);
	ungetc(c_read, f);
	return (0);
}

int scan_char(FILE *f, va_list ap)
{
	char	c = fgetc(f);

	if (c == EOF) {
		if (ferror(f))
			return (-1);
		return (0);
	}
	char	*c_ptr = va_arg(ap, char *);
	*c_ptr = c;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	char	c = fgetc(f);
	if (c == EOF) {
		if (ferror(f))
			return (-1);
		return (0);
	}
	int sign = 1;
	if (c == '+' || c == '-') {
		if (c == '-')
			sign = -sign;
	}
	else
		ungetc(c,f);
	int	number = 0;
	int	digits = 0;
	while ((c = fgetc(f)) != EOF) {
		if (isdigit(c)) {
			number = number * 10 + (c - '0');
			digits++;
		}else {
			ungetc(c, f);
			break;
		}
	}
	if (ferror(f))
		return (-1);
	if (!digits) {
		return(0);	
	}
	int	*n_ptr = va_arg(ap, int *);
	*n_ptr = number * sign;
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char	c = fgetc(f);
	if (c == EOF) {
		if (ferror(f))
			return (-1);
		return (0);
	}
	ungetc(c, f);
	char	*str = va_arg(ap, char *);
	int	char_read = 0;
	while((c = fgetc(f)) != EOF) {
		if (isspace(c)) {
			ungetc(c, f);
			break;
		}
		*str = c;
		char_read++;
		str++;
	}
	if (ferror(f))
		return (-1);
	if (!char_read)
		return (0);
	*str = '\0';
	return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);
	int	ret;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret = match_conv(f, &format, ap);
			if (ret == 0)
				break ;
			else if (ret == -1)
				return (EOF);
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list	ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

 int main()
 {
 	int number = 99;
 	char character;
 	char string[500];
	int counter = 0;
 	counter += ft_scanf("  %d", &number);
 	counter += ft_scanf(" %c", &character);
 	counter += ft_scanf(" %s", &string);
	printf("negrata");
 	printf("the number you entered is %d\n", number);
 	printf("the character you entered is %c\n", character);
 	printf("the string you entered is %s\n", string);
 	printf("variables asignadas%d\n", counter);
 	return 0;
 }

