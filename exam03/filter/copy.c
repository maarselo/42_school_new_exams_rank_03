#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strncmp(char *s1, char *s2, int len) {
	int	i = 0;

	while (s1[i] && s2[i] && i < len - 1 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	main(int argc, char **argv) {
	if (argc != 2 || !strlen(argv[1]))
		return (1);
	int	i;
	int	len = strlen(argv[1]);
	int	bytes_read;
	char	buffer[1000];
	
	do {
		bytes_read = read(0, buffer, sizeof(buffer));
		if (bytes_read == -1)
			return (perror("Error"), 1);
		i = 0;
		while (i < bytes_read) {
			if (i + len <= bytes_read && !ft_strncmp(buffer + i, argv[1], len)) {
				for (int j = 0; j < len; j++)
					printf("*");
				i += len;
			}else
				printf("%c", buffer[i++]);
		}
	}while(bytes_read > 0);
}



