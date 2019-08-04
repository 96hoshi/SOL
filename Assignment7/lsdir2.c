/*
  Scrivere un programma C chiamato 'lsdir' che,
  dato come argomento un nome di directory,
  visita ricorsivamente tutto il sottoalbero di directory 
  che ha come radice la directory passata come argomento. 
  Per ogni directory, il programma deve stampare sullo standard output 
  le informazioni sui file nel seguente formato: 
  Directory: <nomedir1>
	file1     size    permessi
	file2     size    permessi
	------------------
	Directory: <nomedir2>
	file3     size    permessi
	file4     size    permessi
	------------------
  dove la directory 'nomedir1' contiene i file 'file1' e 'file2' e 
  la directory 'nomedir2'. Durante la visita dell'albero di directory 
  non cosiderare le directory '.' e '..'. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>

#define BUFFSIZE 1024

void printattr(char *file_name)
{
	struct stat info;

	stat(file_name, &info);

	printf("%8s\t", file_name);
	printf("%8ld\t", info.st_size);
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
	printf("\n");
}

int is_legal_dir(char *file_name)
{
	if (strcmp(file_name, ".") != 0 && strcmp(file_name, "..") != 0)
		return 1;
	return 0;
}

void processdir(void)
{
	DIR *d;
	struct dirent *file;
	char buff[BUFFSIZE];


	if ((d = opendir(".")) == NULL) {
		perror("opendir");
		exit(EXIT_FAILURE);
	}

	 if (getcwd(buff, BUFFSIZE) == NULL){ //per stampare il path della dir corrente
		perror("getcwd");
		exit(EXIT_FAILURE);
	}

	//strcat(buff, "./");

	printf("Directory: %s\n", buff); /*nome dir*/

	while ((errno = 0, file = readdir(d)) != NULL) {
		if (is_legal_dir(file->d_name))
			printattr(file->d_name);
	}
	if (errno != 0){
		perror("readdir");
		exit(EXIT_FAILURE);
	}
	printf("-----------------------------\n");
	//file analizzati
	rewinddir(d);
	//analizzo le cartelle
	while ((errno = 0, file = readdir(d)) != NULL) {
	 	if (file->d_type == DT_DIR){
			if (is_legal_dir(file->d_name)){
				chdir(file->d_name);
				
				// strcat(buff, "/");
				// strcat(buff, file->d_name)
				processdir(); 
			}
		}
	}
	if (errno != 0){
		perror("readdir");
		exit(EXIT_FAILURE);
	}

	if (closedir(d) == -1) {
		perror("closedir");
		exit(EXIT_FAILURE);
	}

	if (chdir("..") == -1) { //mi posiziono nella cartella precedente
		perror("chdir");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]){

	if (argc < 1) {
		perror("Non ci sono abbastanza argomenti");
		exit(EXIT_FAILURE);
	}

	if (chdir(argv[1]) == -1) { //mi posiziono nella cartella passata 
		perror("chdir");
		exit(EXIT_FAILURE);
	}
	processdir();
	return 0;
}




// // path della directory corrente
//  getcwd(buff, buffsize)
//  //mi posiziono nella cartella passata come argomento
//  chdir(argv[1])
//  //scandisco i file della cartella corrente(cartelle e non, evitando . e ..)
//  processdir()

// 	 opendir(".")
// 	 if (getcwd(buff, BUFFSIZE) == NULL){ //mi serve per stampare il path della dir corrente
// 		perror("getcwd");
// 		exit(EXIT_FAILURE);
// 	}
// 	print(buff:\n)
// 	 ndir = countdir(path)
// 	 char *array[ndir] //array che contiene tutti i path delle cartelle
// 	 i = 0
// 	 while (file = readdir(d) != NULL)
// 	 	if (isdir(file)) //with d_type e DT_DIR(file.d_type)
// 			if (strcmp(file->d_name, ".") != 0 || strcmp(file->d_name, "..") != 0 )
// 		 		array[i++] = file->d_name

// 	 	else printattr(file)

// 	 for (i = 0; i < ndir; ++i)
// 	 	chdir(array[i])
// 	 	processdir()
// 	 opendir("..")


