#include <stdio.h>
#include <stdlib.h>

int sum_required;
void	ft_print_solution(int total_powersets, int *powersets) {
	for (int i = 0; i < total_powersets; i++) {
		printf("%d", powersets[i]);
		if (i < total_powersets - 1)
			printf(" ");
	}
	printf("\n");
}
int 	calcular_sum(int total_powersets, int *powersets)
{
	int actual_sum = 0;
	for (int i = 0; i < total_powersets; i++)
	{
		actual_sum += powersets[i];
	}
	return actual_sum;
}
void	ft_solve(int start, int total_powersets, int total_numbers, int *powersets, int *numbers) {
	if (start == total_numbers)	
	{
		if (calcular_sum(total_powersets, powersets) == sum_required && total_powersets != 0)
		{
			ft_print_solution(total_powersets, powersets);
		}
		return ; 
	}
		
		ft_solve(start + 1, total_powersets, total_numbers, powersets, numbers);
		powersets[total_powersets] = numbers[start];
		
		ft_solve(start + 1, total_powersets + 1, total_numbers, powersets, numbers);
}

int	main(int argc, char **argv) {
	if (argc  < 3)
		return (0);
	int	total_numbers = argc - 2;
	sum_required = atoi(argv[1]);
	if (sum_required == 0)
	{
		printf("\n");
	}
	int	*powersets = (int *)malloc(sizeof(int) * total_numbers);
	int	*numbers = (int *)malloc(sizeof(int) * total_numbers);
	int 	j = 2;
	for (int  i = 0; i < total_numbers; i++) {
		numbers[i] = atoi(argv[j++]);
	}
	ft_solve(0, 0, total_numbers, powersets, numbers);
	
}
