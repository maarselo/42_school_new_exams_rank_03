#include "gnl.h"

int	ft_strlen(char *str) {
	int	i=0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char c, char *str) {
	int	i = 0;
	while(str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (str + i);
	return (NULL);
}

char	*ft_substr(int start, int len, char *str) {
	int	i= -1;
	char	*substr = (char*)malloc(len + 1);
	while (++i < len)
		substr[i] = str[i + start] ;
	substr[i] = '\0';
	return (substr);
}

void	ft_buffjoin(char *tmp_buffer, char **buffer) {
	char	*tmp = *buffer;
	int	len_buffer = ft_strlen(*buffer);
	int	len_tmp_buffer = ft_strlen(tmp_buffer);
	int	i,j;
	*buffer = (char *)malloc(len_buffer + len_tmp_buffer + 1);
	
	for (i = 0; i < len_buffer; i++)
		(*buffer)[i] = tmp[i];
	for (j = 0; j < len_tmp_buffer; j++)
		(*buffer)[i + j] = tmp_buffer[j];
	(*buffer)[i + j] = '\0';
	free(tmp);
}

char	*ft_getline(char *buffer) {
	int	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (ft_substr(0, i, buffer));
}

void	ft_nextline(char **buffer) {
	int	i = 0;
	char	*tmp = *buffer;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	*buffer = ft_substr(i, ft_strlen(tmp) - i, *buffer);
	free(tmp);
}

void	ft_read(char **buffer, int fd) {
	int	bytes_read;
	char	*tmp_buffer = malloc(BUFFER_SIZE + 1);
	
	do {
		bytes_read = read(fd, tmp_buffer, BUFFER_SIZE);
		tmp_buffer[bytes_read] = '\0';
		ft_buffjoin(tmp_buffer, buffer);
	} while (bytes_read > 0 && ft_strchr('\n', tmp_buffer));
	free(tmp_buffer);
}

char	*get_next_line(int fd) {
	static char	*buffer;
	char		*line;
	
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	ft_read(&buffer, fd);
	if (!buffer ||!*buffer) {
		if (buffer){
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	line = ft_getline(buffer);
	ft_nextline(&buffer);
	return (line);

}

#include <fcntl.h>
#include <stdio.h>

int 	main(int argc, char **argv) {
	int fd = open(argv[1], O_RDONLY);
	char *line = get_next_line(fd);	
	int 	i = 0;
	while (line) {
		printf("%i linea->%s\n",i++, line);
		free(line);
		line = get_next_line(fd);
	}
	printf("ultima->%s", get_next_line(fd));	

}

