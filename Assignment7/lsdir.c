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

#define BUFFSIZE 256

void printattr(char *file_name)
{
	struct stat info;

	stat(file_name, &info);

	printf("%s\t", file_name);
	printf("%ld\t", info.st_size);
	//printf("%10.10s\n", sperm(info.st_mode)); //permessi
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

	printf("%s\n", buff); /*nome dir*/

	int ndir = 10;	//int ndir = countdir(buff); da definire
	char *directories[ndir]; //array che contiene tutti i path delle cartelle
	size_t i = 0;
	while ((errno = 0, file = readdir(d)) != NULL){
	 	if (file->d_type == DT_DIR) //isdir
			if (strcmp(file->d_name, ".") != 0 || strcmp(file->d_name, "..") != 0 )
				directories[i++] = file->d_name;
		else
			printattr(file->d_name);
	}
	if (errno == -1){
		perror("readdir");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < ndir; ++i){
		chdir(directories[i]);
		processdir();
	}

	if (closedir(d) == -1) {
		perror("closedir");
		exit(EXIT_FAILURE);
	}
	opendir("..");
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


