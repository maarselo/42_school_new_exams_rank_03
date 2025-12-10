#include "copy.h"

void ft_put_null(char *buffer) {
	for (int i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = '\0';
}

int	ft_strlen(char *str) {
	int	i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char c, char *str) {
	int	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (str + i);
	return (NULL);
}

char	*ft_strdup(char *str) {
	char	*dup;
	int	len = ft_strlen(str);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	for (int i  = 0; i < len; i++)
		dup[i] = str[i];
	dup[len] = '\0';
	return (dup);
}

char	*ft_substr(int start, int len, char *str) {
	char	*substr;
	if (!str)
		return (NULL);
	int	s_len = ft_strlen(str);
	substr = (char*)malloc(sizeof(char) * (len + 1));
	for (int i = 0; i < len; i++)
		substr[i] = str[i + start];
	substr[len] = '\0';
	return (substr);
}

void	ft_buffjoin(char *tmp_buffer, char **buffer) {
	char	*tmp = *buffer;
	if (!*buffer)
	{
		*buffer = ft_substr(0, ft_strlen(tmp_buffer), tmp_buffer);
		return;	
	}
	int len = ft_strlen(tmp_buffer) + ft_strlen(tmp);
	*buffer = (char *)malloc(sizeof(char) * (len + 1));
	for (int i = 0; i < ft_strlen(tmp); i++)
		(*buffer)[i] = tmp[i];
	for (int i = 0; i < ft_strlen(tmp_buffer); i++)
		(*buffer)[i + ft_strlen(tmp)] = tmp_buffer[i];
	(*buffer)[len] = '\0';
	free(tmp);
}

char	*ft_getline(char *buffer) {
	int	i = 0;

	if (!buffer)
		return NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (ft_substr(0, i, buffer));
}


void	ft_nextline(char **buffer) {
	int	i = 0;
	
	if (!buffer || !*buffer)
		return ;

	char	*tmp = *buffer;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	*buffer	 = ft_substr(i, ft_strlen(tmp)- i, tmp);
	free(tmp);
}

void	ft_read(char **buffer, int fd) {
	int	bytes_read;
	char	*tmp_buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);

	do {
		bytes_read = read (fd, tmp_buffer, BUFFER_SIZE);
		tmp_buffer[bytes_read] = '\0';
		ft_buffjoin(tmp_buffer, buffer);
	}while (bytes_read > 0 && !ft_strchr('\n', tmp_buffer));
	free(tmp_buffer);
}


char	*get_next_line(int fd) {
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	ft_read(&buffer, fd);
	if (!buffer || !*buffer)
	{
		if (buffer){
			free(buffer);buffer=NULL; }
		return ( NULL);
	}
	line = ft_getline(buffer);
	ft_nextline(&buffer);
	return (line);
}

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


