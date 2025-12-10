#include <stdio.h>

int	ft_strlen(char *str) {
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_swap(char *s1, char *s2) {
	char	tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	ft_sort(char *str) {
	int	i= 0;
	
	while (str[i]) {
		if (str[i + 1] && str[i] > str[i + 1]) {
			ft_swap(&str[i], &str[i + 1]);
			i = 0;
		}else
			i++;
	}
}

void	ft_permute(int start, char *str) {
	if (start == ft_strlen(str))
		puts(str);
	int i = start;
	while (i < ft_strlen(str)) {
		ft_swap(&str[i], &str[start]);
		ft_permute(start + 1, str);
		ft_swap(&str[i], &str[start]);
		i++;
	}
}

int	main(int argc, char**argv) {
	if (argc != 2)
		return (1);
	ft_sort(argv[1]);
	ft_permute(0, argv[1]);
}
