#include <stdio.h>
#include <stdlib.h>

int main(int arg, char* argv[]){
	FILE *file = fopen("index.txt", "rt");
	if(file != NULL && !feof(file)){
		char name[10];
		char* text = fgets(name, 9, file);
		puts(text);
	}else{
		puts("fix your shit");
	}
}
