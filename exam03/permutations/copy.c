#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str) {
	int	i = 0;	
	while (str[i]) 
		i++;
	return (i);
}	

void	ft_swap(char *char1, char *char2) {
	char	tmp;
	
	tmp = *char1;
	*char1 = *char2;
	*char2 = tmp;
}

void	ft_sort(char *str) {
	int len = ft_strlen(str);
	int i = 0;
	while (i < len) {
		if (str[i + 1] && str[i] > str[i + 1]) {
			ft_swap(&str[i], &str[i + 1]);
			i = 0;
		}else
			i++;
	}
}

void	ft_permutations(int start, char *str) {
	int	len = ft_strlen(str);
	if (start >= len)
		puts(str);
	int i = start;
	while (i < len) {
		ft_swap(&str[i], &str[start]);
		ft_permutations(start + 1, str);
		ft_swap(&str[i], &str[start]);
		i++;
	}
}




int	main(int argc, char **argv) {
	if (argc != 2 || !ft_strlen(argv[1]))
		return (1);
	ft_sort(argv[1]);
	ft_permutations(0, argv[1]);	
}
