#include <stdio.h>
#include "tokenizer.h"

int main(int argc, char *argv[]){
	int x, x_r;

	x_r = tokenizer_r(argc,argv);
	x = tokenizer(argc,argv);

	return 0;
}
