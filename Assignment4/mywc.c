/*Scrivere un programma che implementa una versione semplificata 
 del comando Unix wc limitatamente alle opzioni -l e -w (man 1 wc).
 Usare getopt per il parsing degli argomenti (man 3 getopt). 
 Se non vengono passate opzioni, il programma stampa sia il numero
 di linee che il numero di parole del/dei file i cui nomi sono passati
 come argomento (mywc [-l -w] file1 [file2 file3 ….]). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define MAX_STRING 1024
#define EXIT_TRUE 1
#define EXIT_FALSE 0

void check_alloc(void * ptr, int b, const char *s){
	if(ptr == NULL){
		fprintf(stderr, "%s\n", s);
		if(b)
			exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]){
	int line_count = 0, word_count = 0;
	int l = 0, w = 0; 
	int opt = 0;

	while((opt = getopt(argc, argv, "wl")) != -1){
		if(opt == 'l'){
			l = 1;
		}
		if(opt == 'w'){
			w = 1;
		}
	}
	if(!l && !w){
		l = 1;
		w = 1;
	}

	char **files = argv + optind;
	int files_count = argc - optind;

	int *arr_lines = (int *)calloc(files_count, sizeof(int));
	check_alloc(arr_lines, EXIT_TRUE, "Calloc lines");

	int *arr_words = (int *)calloc(files_count, sizeof(int));
	check_alloc(arr_words, EXIT_TRUE, "Calloc words");

	for(size_t i = 0; i < files_count; ++i){
		FILE *input = fopen(files[i], "r");
		if(input == NULL){
			fprintf(stderr, "wc: %s: File o directory non esistente\n", files[i]);
			arr_lines[i] = -1;
			arr_words[i] = -1;
			continue;
		}
		int ch;
		int lines = 0;
		int words = 0;

		if(l){
			while((ch = fgetc(input)) != EOF)
				if(ch == '\n')
					lines++;
			arr_lines[i] = lines;
		}
		if(w){
			rewind(input);
			words = 0;
			char string[MAX_STRING];
			while(fscanf(input, "%s", string) != EOF)
				words++;
			arr_words[i] = words;
		}

		line_count += lines;
		word_count += words;

		fclose(input);
	}

	int digits_l = (int)log10f(line_count) + 1;
	int digits_w = (int)log10f(word_count) + 1;

	for(size_t i = 0; i < files_count; ++i){
		if(arr_lines[i] >= 0 && arr_words[i] >= 0){
			if(l)
				printf(" %*d", digits_l, arr_lines[i]);
			if(w)
				printf(" %*d", digits_w, arr_words[i]);
			printf(" %s\n", files[i]);
		}
	}

	if(l) printf(" %*d", digits_l, line_count);
	if(w) printf(" %*d", digits_w, word_count);
	printf(" totale\n");

	free(arr_lines);
	free(arr_words);
	return 0;
}
