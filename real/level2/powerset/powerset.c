#include <stdlib.h>
#include <stdio.h>

int	have_solution = 0;

int	ft_has_negatives(int start, int total_numbers, int *numbers) {
	for (int i = start; i < total_numbers; i++)
		if (numbers[i] < 0)
			return (1);
	return (0);
}

int	ft_have_cero(int start, int total_numbers, int  *numbers) {
	for (int i = start; i < total_numbers; i++)
		if (numbers[i] == 0)
			return (1);
	return (0);
}

void	ft_print_solution(int *powersets, int total_powersets) {
	for (int i =0; i < total_powersets; i++) {
		printf("%d", powersets[i]);
		if (i < total_powersets - 1)
			printf(" ");
	}
	printf("\n");
}

void	ft_solve(int start, int sum, int sum_required, int total_powersets, int total_numbers, int *powersets, int *numbers){
	if (sum == sum_required && total_powersets && !ft_have_cero(start, total_numbers, numbers))
		return (have_solution = 1, ft_print_solution(powersets, total_powersets));
	else if (sum > sum_required && !ft_has_negatives(start, total_numbers, numbers))
		return ;
	while (start < total_numbers) {
		powersets[total_powersets] = numbers[start];
		ft_solve(start + 1, sum + numbers[start],sum_required, total_powersets + 1, total_numbers, powersets, numbers);
		start++;
	}
}



int	main(int argc, char **argv) {
	if (argc < 3)
		return (0);
	int	total_numbers = argc - 2;
	int	sum_required = atoi(argv[1]);
	if (sum_required == 0)
		printf("\n");
	int	*numbers = (int *)malloc(sizeof(int) * total_numbers);
	int	*powersets = (int *)malloc(sizeof(int) * total_numbers);
	int	j = 2;
	for (int i = 0; i < total_numbers; i++)
		numbers[i] = atoi(argv[j++]);
	ft_solve(0,0, sum_required, 0, total_numbers, powersets, numbers);
	if (have_solution == 0 && sum_required != 0)
		printf("\n");
	free(numbers);
	free(powersets);
}
