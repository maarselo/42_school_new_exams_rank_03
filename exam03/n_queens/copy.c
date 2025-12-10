#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	board_size;
int	*queens;

void	ft_printf_solution() {
	for (int i = 0; i < board_size; i++) {\
		fprintf(stdout, "%d", queens[i]);
		if (i < board_size - 1)
			fprintf(stdout, " ");
	}
	fprintf(stdout, "\n");
}

int	ft_abs(int number) {
	if (number < 0)
		return -number;
	return number;
}

int	ft_issafe(int row, int col) {
	for (int i = 0 ; i < col; i++) {
		if (queens[i] == row)
			return (0);
		if (ft_abs(queens[i] - row) == ft_abs(i - col))
			return (0);
	}
	return (1);
}

void	ft_solve(int col) {
	if (col == board_size)
		return (ft_printf_solution());
	for (int row = 0; row < board_size; row++) {
		if (ft_issafe(row, col)) {
			queens[col] = row;
			ft_solve(col + 1);
		}
	}
}

int	main(int argc, char **argv) {
	if (argc != 2 || atoi(argv[1]) < 0)
		return (1);
	if (atoi(argv[1]) >= 0 && atoi(argv[1]) <= 3)
		return (printf("\n"), 0);
	board_size = atoi(argv[1]);
	queens = (int *) malloc(sizeof(int) * atoi(argv[1]));
	ft_solve(0);
	free(queens);
}

