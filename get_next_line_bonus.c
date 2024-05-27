/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamorim <raamorim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:22:01 by marvin            #+#    #+#             */
/*   Updated: 2024/05/27 13:55:09 by raamorim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	line[FOPEN_MAX][BUFFER_SIZE + 1] = {0};
	char		*gnl;
	int			bytes_read;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
		return (NULL);
	gnl = malloc(1);
	if (!gnl)
		return (NULL);
	gnl[0] = '\0';
	gnl = ft_strjoin(gnl, line[fd]);
	if (check_and_clear(line[fd]) == 1)
		return (gnl);
	bytes_read = read(fd, line[fd], BUFFER_SIZE);
	if (bytes_read <= 0 && !(*gnl))
		return (free_gnl(gnl));
	while (bytes_read > 0)
	{
		line[fd][bytes_read] = '\0';
		gnl = ft_strjoin(gnl, line[fd]);
		if (check_and_clear(line[fd]) == 1)
			break ;
		bytes_read = read(fd, line[fd], BUFFER_SIZE);
	}
	return (gnl);
}

/* int main() {
	// Suponha que você tenha três arquivos abertos simultaneamente
	FILE *file1 = fopen("arquivo1.txt", "r");
	FILE *file2 = fopen("arquivo2.txt", "r");
	FILE *file3 = fopen("arquivo3.txt", "r");

	// Verifica se os arquivos foram abertos corretamente
	if (file1 == NULL || file2 == NULL || file3 == NULL) {
		perror("Erro ao abrir arquivo");
		return (EXIT_FAILURE);
	}

	// Lê e imprime as linhas dos arquivos usando get_next_line
	char *linha1 = get_next_line(fileno(file1));
	char *linha2 = get_next_line(fileno(file2));
	char *linha3 = get_next_line(fileno(file3));

	printf("Linha do arquivo1.txt: %s\n", linha1);
	printf("Linha do arquivo2.txt: %s\n", linha2);
	printf("Linha do arquivo3.txt: %s\n", linha3);

	// Libera a memória alocada para as linhas
	free(linha1);
	free(linha2);
	free(linha3);

	// Fecha os arquivos
	fclose(file1);
	fclose(file2);
	fclose(file3);

	return (EXIT_SUCCESS);
} */