#include <stdlib.h>
#include <stdio.h>

int	*queens;
int	board_size;

void	ft_print_solution() {
	for (int i = 0; i < board_size; i++) {
		printf("%d", queens[i]);
		if (i < board_size - 1)
			printf(" ");
	}
	fprintf(stdout, "\n");
}

int	ft_abs(int number) {
	if (number < 0)
		return (-number);
	return (number);
}

int	ft_issafe(int col, int row) {
	for (int i = 0; i < col; i++) {
		if (queens[i] == row)
			return (0);
		if (ft_abs(queens[i] - row) == ft_abs(i - col))
			return (0);
	}
	return (1);
	
}

void	ft_solve(int col) {
	if (col == board_size)
		return (ft_print_solution());
	for (int row = 0; row < board_size; row++) {
		if (ft_issafe(col, row)) {
			queens[col] = row;
			ft_solve(col + 1);
		}
	}
	
}

int	main(int argc, char **argv) {
	if (argc != 2 || atoi(argv[1]) < 0)
		return (1);
	board_size = atoi(argv[1]);
	if (0 <= board_size && board_size <= 3)
		return (fprintf(stdout, "\n"));
	queens = (int *)malloc(sizeof(int) * board_size);
	ft_solve(0);
	free(queens);
}
