#include <stdio.h>
#include <stdlib.h>

int main(int arg, char* argv[]){
	swap(2,3);
}

void swap(int *x, int *y){
	int temp = &x;
	x = *temp2;
	printf("x = %d, y = %d", x, y);
}
