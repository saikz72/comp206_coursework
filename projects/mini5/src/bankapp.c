/*
 * this program
 ** ******************************************************************
 *Author		Dept 		Date		Notes
 **********************************************************************
 *Saikou		Software eng	Mar 10, 2020    initial version
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function protoype

int addAccount(char* accNum, char* str, FILE *file);

const char* del = ",";

int main(int argc, char* argv[]){
	if( argc == 1)
	{
		fprintf(stderr, "%s", "Error, incorrect usage!\n -a ACCTNUM NAME\n -d ACCTNUM DATE AMOUNT\n -w ACCTNUM DATE AMOUNT\n");
		return 1;
	}
	else if( argc == 3 && argv[1][1] == 'a' )
	{
		fprintf(stderr, "%s", "Error, incorrect usage!\n -a ACCTNUM NAME\n");
		return 1;
	}
	else if( argc == 3 && argv[1][1] == 'w' )
	{
		fprintf(stderr,"%s", "Error, incorrect usage!\n -w ACCTNUM DATE AMOUNT\n");
		return 1;
	}	
	else if( argc == 4 && argv[1][1] == 'd')
	{
		fprintf(stderr,"%s", "Error, incorrect usage!\n -d ACCTNUM DATE AMOUNT\n");
		return 1;
	}
	else
	{
		FILE *file = fopen("bankdata.csv", "a+");
		if(file == NULL)
		{
			fprintf(stderr,"%s", "Error, unable to locate the data file bankdata.csv\n");
			return 100;
		}else
		{
			char checker = argv[1][1];
			if(checker == 'a' && addAccount(argv[2], argv[3], file) == 50)
			{
				fprintf(stderr, "%s", "Error, account number 1024 already exist\n");
				return 50;
			}
			else
			{
				fprintf(file, "AC,%s,%s\n", argv[2], argv[3]);  
			}
		}
	}


}

/*
*methods writes data to the bankdata.csv file
*/

int addAccount(char* accNum, char* str, FILE *file){
	//char accNumStr[10];		//to convert int to a string
	char arr2[4000];		//to store contents of file
		
	char* fileArray = fgets(arr2, 3999, file);	
	//sprintf(accNumStr, "%d", accNum);		//convert accNum to a string		
	char *ptr = strtok(fileArray, del);
		
	while(ptr != NULL && !feof(file)){
		if(strcmp(accNum, ptr) == 0){
 			return 50;
		}else{
			ptr = strtok(NULL, del);
		}	
	}	
	return 100;
}

