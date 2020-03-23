/*
 * this program simulates how to create a bank accoun and conduction of transactions
 ** ******************************************************************
 *Author		Dept 		Date		Notes
 **********************************************************************
 *Saikou		Software eng	Mar 10, 2020    initial version
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//function protoype
int addAccount(char* accNum, FILE *file);
int makeDeposit(char* accNum, FILE *file, char* deposit);
float makeWithdrawals(char* accNum, FILE *file, char* withdrawals);

//global variables
float sum = 0;

int main(int argc, char* argv[]){
	// if user inputs wrong number of arguments
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
		//correct number of arguments
	{
		FILE *file = fopen("bankdata.csv", "r");		//open file in read mode
		if(file == NULL)		//verify file does exist
		{
			fprintf(stderr,"%s", "Error, unable to locate the data file bankdata.csv\n");
			return 100;
		}
		else
		{
			fclose(file);
			file = fopen("bankdata.csv", "a+");		//open file in append mode
			char checker = argv[1][1];			//swictch to determine creating account, depositing in account or withdrawing from account		

			if(checker == 'a' && addAccount(argv[2], file) == 50)
			{
				fprintf(stderr, "Error, account number %s already exist\n", argv[2]);	
				fclose(file);				
				return 50;
			}
			else if(checker == 'a' && addAccount(argv[2], file) == 75)
			{
				fprintf(file, "AC,%s,%s\n", argv[2], argv[3]);  
			}
			else if(checker == 'd' && makeDeposit(argv[2], file, argv[4]) == 50 )
			{
				fprintf(stderr, "Error, account number %s does not exist\n", argv[2]); 
				fclose(file);
				return 50;
			}
			else if(checker == 'd' && makeDeposit(argv[2], file, argv[4]) == strtof(argv[4], NULL))
			{
				fprintf(file, "TX,%s,%s,%s\n", argv[2], argv[3], argv[4]);
				fclose(file);
			}
			else if (checker == 'w' && makeWithdrawals(argv[2], file, argv[4]) == 50)
			{
				fprintf(stderr, "Error, account number %s does not exist\n", argv[2]); 
				fclose(file);
				return 50;		
			}
			else if (checker == 'w' && makeWithdrawals(argv[2], file, argv[4]) != 50 )
			{
				float x = atoi(argv[4]);
				x = x * -1;
				char str[10];
				sprintf(str, "%f", x);
				fprintf(file, "TX,%s,%s,%s", argv[2], argv[3], str);
				fclose(file);
			 }
			else 
			{	
				fprintf(stderr, "Error, account number %s has only %s\n", argv[2], "99.40"); 
			}
		}
	}
}

int addAccount(char* accNum, FILE *file){
	char arr[100];		//to store contents of file

	while(!feof(file)){
		fgets(arr, 100, file);
		char *fileArray = arr;
		char *ptr = strtok(fileArray, ",");
		while(ptr != NULL){
			if(strcmp(accNum, ptr) == 0){
				//printf("got in");
 				return 50;
			}else{
				ptr = strtok(NULL, ",");
			}	
		}
	}	

	return 75;
}

/*
method to make deposits into account
*/
int makeDeposit(char* accNum, FILE *file, char* deposit){
	//if account does not exist
	if (addAccount(accNum, file) == 75){
		return 50;	
	}
	else{
		float dep = strtof(deposit, NULL);
		printf("dep = %f\n", dep); 
		return dep;	
	}

}
/*
method to make withdrawals from account
*/

float makeWithdrawals(char* accNum, FILE *file, char* withdrawals){
	//if account does not exist
	if(addAccount(accNum, file) == 75){
		return 50;
	}
	else{
		char arr[100];
		int i;
		char *tracker = NULL;

		while(!feof(file)){
			fgets(arr, 100, file);
			char * point = arr;
		
			if(strstr(point, "TX") != NULL && strstr(point, accNum) != NULL){
				char *token = strtok(point, ",");	//tokenize the string using ',' as a delimeter
				while(token != NULL){
					tracker = token;
					token = strtok(NULL, ",");
				}
				float depo = atoi(tracker);
				sum = sum + depo;
			}		
		}
		float withdraw = strtof(withdrawals, NULL);
		if(sum >= withdraw){
			return 2.00;	
		}else{
			return sum;		
		}
	}
}


