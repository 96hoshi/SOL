/*
 Scrivere un programma C che dati come argomenti una lista di file
  o directories stampa per ogni argomento:
  il nome del file/directory,
  il numero dell'inodo corrispondente,
  il tipo di file (-,l,d,s,…)
  la machera di bit di protezione (es. rw-r–r–),
  l'user identifier (uid),
  il group identifier (gid),
  la size del file 
  ed il timestamp dell'ultima modifica.
  Per convertire il tempo di ultima modifica in un formato stampabile
  usare la funzione di libreria ctime.
  Usare getpwuid e getgrgid per convertire uid e gid nei nomi corrispondenti
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

void print_stats(char *path)
{
	struct stat info;
	struct group *grp;
	struct passwd *pwd;

	stat(path, &info);

	printf("Name: %s", path);
	printf("\nI-node: %ld", (long)info.st_ino);
	printf("\nType: ");
	if (S_ISREG(info.st_mode)) printf("regular");
	else if (S_ISDIR(info.st_mode)) printf("directory");
	else if (S_ISLNK(info.st_mode)) printf("link simb");
	else if (S_ISCHR(info.st_mode)) printf("character special file");
	else if (S_ISBLK(info.st_mode)) printf("block special file");
	else if (S_ISFIFO(info.st_mode)) printf("pipe");
	else if (S_ISSOCK(info.st_mode)) printf("socket");
	else printf("non riconosciuto");

	printf("\nMask: ");
	/* user */
	if (S_IRUSR & info.st_mode) putchar('r');
	else putchar('-');
	if (S_IWUSR & info.st_mode) putchar('w');
	else putchar('-');
	if (S_IXUSR & info.st_mode) putchar('x');
	else putchar('-');
	/* group */
	if (S_IRGRP & info.st_mode) putchar('r');
	else putchar('-');
	if (S_IWGRP & info.st_mode) putchar('w');
	else putchar('-');
	if (S_IXGRP & info.st_mode) putchar('x');
	else putchar('-');
	/* others */
	if (S_IROTH & info.st_mode) putchar('r');
	else putchar('-');
	if (S_IWOTH & info.st_mode) putchar('w');
	else putchar('-');
	if (S_IXOTH & info.st_mode) putchar('x');
	else putchar('-');

	if ((pwd = getpwuid(info.st_uid)) != NULL)
		printf("\nUser identifier: %s", pwd->pw_name);
	else
		printf(" %d", info.st_uid);

	if ((grp = getgrgid(info.st_gid)) != NULL)
		printf("\nGroup identifier: %s", grp->gr_name);
	else
		printf(" %d", info.st_gid);

	printf("\nSize: %ld", info.st_size); 
	printf("\nLast modified: %s\n", ctime(&info.st_mtime));

}

int main(int argc, char *argv[]) {
	int fd = 0, l = 0, i = 0;

	if (argc < 1) {
		perror("Input vuoto");
		exit(EXIT_FAILURE);
	}

	argc--;
	argv++;

	for (i = 0; i < argc; ++i) {
		fd = open(argv[i], O_RDONLY);
		if (fd != -1) {
			print_stats(argv[i]);
			close(fd);
		} else {
			perror("s.c: Impossibile aprire il file");
		}
	}

	return 0;
}