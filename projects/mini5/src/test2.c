#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int arg, char* argv[]){
	int digits = 0, letters = 0, extras = 0, index;
	char message[] = {'1', '2', 'd', '.', 'e', '3','/','\0'};

	for(index = 0; index < strlen(message); index++){
		if(isalpha(message[index]))
			letters++;
		else if(isdigit(message[index]))
			digits++;
		else
			extras++;
	}
	printf("numbers = %d , letters = %d, extras = %d\n", digits, letters, extras);
}
