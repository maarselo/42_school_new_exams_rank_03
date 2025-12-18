#include <stdlib.h>
#include <stdio.h>

void	ft_print_solution(int *queens, int board_size) {
	for (int i = 0; i < board_size; i++) {
		fprintf(stdout, "%d", queens[i]);
		if (i < board_size - 1)	
			fprintf(stdout, " ");
	}
	fprintf(stdout,"\n");
}

int	ft_abs(int number) {
	if (number < 0)
		return (-number);
	return (number);
}

int	ft_issafe(int row, int col, int *queens, int board_size) {
	for (int i = 0; i < col; i++) {
		if (queens[i] == row)
			return (0);
		if (ft_abs(queens[i] - row ) == ft_abs(i - col))
			return (0);
	}
	return (1);
}


void	ft_solve(int col, int *queens, int board_size){
	if (col == board_size)
		return (ft_print_solution(queens, board_size));
	for (int row = 0; row < board_size; row++) {
		if (ft_issafe(row, col, queens, board_size)) {
			queens[col] = row;
			ft_solve(col + 1, queens, board_size);
		}
	}
}

int	main(int argc, char **argv) {
	if (argc != 2 || atoi(argv[1]) < 0)
		return(0);
	int	board_size = atoi(argv[1]);
	if (0 <= board_size && board_size <= 3) {
		fprintf(stdout, "\n");
		return (0);
	}
	int	*queens = (int*)malloc(sizeof(int) * board_size);
	ft_solve(0, queens, board_size);
	free(queens);
}

