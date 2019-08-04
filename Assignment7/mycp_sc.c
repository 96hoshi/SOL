/*Scrivere un programma, utilizzando chiamate di sistema,
 che implementi l'equivalente del comando Unix cp.
 Il programma deve accettare 3 argomenti come segue:
 	 mycp_sc filein fileout [buffersize]
 L'argomento 'buffersize' e' la dimensione del buffer da utilizzare
 per le letture e scritture con le SC read e write
 (se non specificato assegnare un valore di default, es. 256bytes)
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	size_t buffersize = 256;
	int in_fd = 0, out_fd = 0;
	int read_l = 0, write_l = 0;
	struct stat info;

	if (argc < 3) {
		perror("Non ci sono abbastanza argomenti");
		exit(EXIT_FAILURE);
	}
	if (argc > 3)
		buffersize = (size_t) strtol(argv[3], NULL, 10);

	if ((in_fd = open(argv[1], O_RDONLY)) == -1){
		perror("s.c:Impossibile aprire fle di input");
		exit(EXIT_FAILURE);
	}
	stat(argv[1], &info);	//per sapere i permessi 

	if ((out_fd = open(argv[2], O_WRONLY | O_CREAT, info.st_mode)) == -1) {
		perror("s.c:Impossibile aprire fle di output");
		close(in_fd);
		exit(EXIT_FAILURE);
	}

	char *buffer = malloc(buffersize * sizeof(char));
	while ((read_l = read(in_fd, buffer, buffersize)) > 0) {
		if (write_l = write(out_fd, buffer, read_l) == -1) {
			perror("s.c: Errore in scrittura");
			close(in_fd);
			close(out_fd);
			exit(EXIT_FAILURE);
		}
	}
	if (read_l == -1) {
		perror("s.c:Errore in lettura");
		close(in_fd);
		close(out_fd);
		exit(EXIT_FAILURE);
	}

	free(buffer);
	close(in_fd);
	close(out_fd);
	return 0;
}
