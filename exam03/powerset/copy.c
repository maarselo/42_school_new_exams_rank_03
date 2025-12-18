#include <stdlib.h>
#include <stdio.h>

void	ft_print_solution(int total_powersets, int *powersets) {
	for (int i = 0; i < total_powersets; i++) {
		printf("%d", powersets[i]);
		if (i < total_powersets - 1)
			printf(" ");
	}
	printf("\n");	
}

void	ft_powerset(int start, int sum, int obj, int total_powersets, int total_numbers, int *powersets, int *numbers) {
	
	if (sum == obj)
		return (ft_print_solution(total_powersets, powersets));
	if (sum > obj)
		return ;
	while (start < total_numbers) {
		powersets[total_powersets] = numbers[start];
		ft_powerset(start + 1, sum + numbers[start], obj, total_powersets + 1, total_numbers, powersets, numbers);
		start++;
	}	
	
}

int	main(int argc, char **argv) {
	if (argc <= 2)
	        return(printf("\n"), 0);
	int	obj = atoi(argv[1]);
	int	total_numbers = argc - 2;
	int	*numbers = (int *)malloc(sizeof(int) * total_numbers);
	int	i = 0;
	int 	j = 2;
	while (i < total_numbers)
		numbers[i++] = atoi(argv[j++]);
	int	*powersets = (int *)malloc(sizeof(int) * total_numbers);
	ft_powerset(0, 0, obj, 0, total_numbers, powersets, numbers);
	free(numbers);
	free(powersets);
}


