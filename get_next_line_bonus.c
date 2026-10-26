/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpoh <jpoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:30:42 by jpoh              #+#    #+#             */
/*   Updated: 2026/10/08 18:44:52 by jpoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	char	*clean;
	int		i;
	int		j;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	j = 0;
	while (stash[i + j])
		j++;
	clean = malloc(j + 1);
	if (!clean)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		clean[j++] = stash[i++];
	clean[j] = '\0';
	return (free(stash), clean);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	readcount;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	readcount = 1;
	while ((!stash || !has_newline(stash)) && readcount > 0)
	{
		readcount = read(fd, buffer, BUFFER_SIZE);
		if (readcount == -1)
		{
			free(buffer);
			return (free(stash), NULL);
		}
		if (readcount > 0)
		{
			buffer[readcount] = '\0';
			stash = ft_strjoin(stash, buffer);
		}
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd] || !*stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = extract_line(stash[fd]);
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         fprintf(stderr, "Usage: %s <file1> [file2] [file3] ...\n", argv[0]);
//         return 1;
//     }

//     int num_files = argc - 1;
//     int *fds = malloc(sizeof(int) * num_files);
//     if (!fds) {
//         perror("malloc failed");
//         return 1;
//     }

//     // 1. Open all files and store their file descriptors
//     int active_files = 0;
//     for (int i = 0; i < num_files; i++) {
//         fds[i] = open(argv[i + 1], O_RDONLY);
//         if (fds[i] == -1) {
//             perror(argv[i + 1]);
//             fds[i] = -1; // Mark as invalid so we skip it later
//         } else {
//             active_files++;
//         }
//     }

//     if (active_files == 0) {
//         free(fds);
//         return 1;
//     }

//     // 2. Interleave reading: pull 1 line from File 1, then File 2, then File 3, etc.
//     int finished_files = 0;
//     while (finished_files < num_files) {
//         for (int i = 0; i < num_files; i++) {
//             if (fds[i] == -1)
//                 continue; // Skip files that failed to open or already reached EOF

//             char *s = get_next_line(fds[i]);
//             if (s != NULL) {
//                 // Print with a prefix so you can clearly see the switching behavior
//                 printf("[%s] %s", argv[i + 1], s);
//                 free(s); // Prevent memory leaks
//             } else {
//                 // File reached EOF or error, close it and mark it inactive
//                 close(fds[i]);
//                 fds[i] = -1;
//                 finished_files++;
//             }
//         }
//     }

//     free(fds);
//     return 0;
// }
