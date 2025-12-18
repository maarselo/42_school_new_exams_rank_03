#include <stdio.h>

int	ft_strlen(char *str) {
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_check(char *str) {
	int	open= 0;
	int	i = -1;
		
	while (str[++i]) {
		if (str[i] == '(')
			open ++;
		else if (str[i] == ')') {
			if (open == 0)
				return (1);
			open--;
		}
	}
	if (open > 0)
		return (1);
	return (0);
}

void	ft_calcule_extra(int *extra_open, int *extra_close, char *str) {
	int	open = 0;
	int	close = 0;
	int	i = -1;
	
	while (str[++i]) {
		if (str[i] == '(')
			open++;
		else if (str[i] == ')') {
			if (open > 0)
				open--;
			else
				close++;
		}
	}
	*extra_open = open;
	*extra_close = close;
}

void	ft_rip(int start,int extra_open, int extra_close, int len, char *str) {
	if (start == len) {
		if (extra_open == 0 && extra_close ==0 && !ft_check(str))
			puts(str);
		return;
	}
	if (extra_open > 0 && str[start] == '(') {
		str[start] = ' ';
		ft_rip(start + 1, extra_open - 1, extra_close, len, str);
		str[start] = '(';
	}
	else if (extra_close > 0 && str[start] == ')') {
		str[start] = ' ';
		ft_rip(start + 1, extra_open, extra_close - 1, len, str);
		str[start] = ')';
	}
	ft_rip(start + 1, extra_open, extra_close, len, str);
}

int	main(int argc, char **argv) {
	if (argc != 2)
		return (0);
	int	len = ft_strlen(argv[1]);
	if (!ft_check(argv[1]))
		return (puts(argv[1]), 1);
	int	extra_open;
	int 	extra_close;
	ft_calcule_extra(&extra_open, &extra_close, argv[1]);
	ft_rip(0,extra_open, extra_close, len,argv[1]);
}

