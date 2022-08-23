/*
 * Alan García 5008 2022
 * Lab 4 assembler
 * Compiled using gcc
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * This function opens a file, 
 * param: name of the file
 * return: pointer to file or NULL if failed
 */
FILE* openFile(char fileName[]){
	FILE *file;
	file = fopen(fileName, "r");
	if(file == NULL){
		printf("Error, could not find file\n");
		exit(1);
	}
	return file;
}

/*
 * This function takes 2 strings, selects substring from one of the strings and compares it.
 * param bigStr: string that provides substring, strinStart: is the index of bigStr, 
 * word: the word we want to compare, size: size of  word and substring
 * return 0 is not equal, return 1 is equal.
*/
int cmprSubstr(char* bigStr, int strStart, char* word, int size){
	//first check if not at the end of the bigStr
	if(strlen(bigStr) < (strStart + size)){
		return 0;
	}
	
	//compare the word to substring
	int b_index = strStart;
	int s_index = 0;
	while(b_index < (strStart + size)){
		if(bigStr[b_index] != word[s_index]){
			return 0;
		}	
		b_index++;
		s_index++;
	}

	return 1;	
}

/*This function takes a string, an array of assembler operations, and its respective
 * value and an array containing number of times each instruction is found; To count 
 * how many cycles and operations are in the given string.
 * param: line: string to be analyzed, opsFound: number of times each operation was found,
 * operations: string array of all the operations, cycleValue: array containing values of 
 * all the operations
 * return result: total number of cycles found in line
 */
int countOps(char* line, int* opsFound, char* operations[],int* cycleValue){
	int cycles = 0;
	int index = 0;
	int i, sizeWord;
	while(index < strlen(line)){
		
		for(i = 0; i < 9 ; i++){
			//current buffer is the size of the word we want.
			sizeWord = strlen( operations[i] );
			
			//compare word with substring
			char* word = operations[i]; 

			if( cmprSubstr(line, index, word, sizeWord) == 1){

				index = index + (sizeWord - 1);
				opsFound[i]++;
				cycles += cycleValue[i];
				//Get out of the for loop if word is found
				break;

			}
		}
		index++;
	}

	return cycles;
}


/*
 * This function takes a pointer to a file and analyses it line by line
 * to count the number of intructions and total number of cycles, then prints
 * the results
 * param: filePtr: pointer to a file
 * return: result of the total number of cycles inside the file
 */
int estimateFile(FILE* filePtr){
	int result = 0;
	// Operations DATA: All arrays must be of the same size.
	int opsFound[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	char* operations[] = {"add", "sub", "mul", "div", "mov", "lea",
			"push", "pop", "ret"};
	int cycleValue[] = {1, 1, 3, 24, 1, 3, 1, 1, 1};
	
	//Check if filePtr is NULL
	if(filePtr == NULL){
		exit(1);
	}
	// read file line by line
	char currentLine[150];
	while(!feof(filePtr)){
		//if fgets fails, it's EOF, we avoid last line copied twice
		if( fgets(currentLine, 150, filePtr) == NULL) break;

		result += countOps(currentLine, opsFound, operations, cycleValue);
	}	
	//print the result for each word;
	int i, instCounter = 0;
	
	for(i = 0; i < 9; i++){
		if(opsFound[i] > 0){
			printf("%s found: %d\n", operations[i], opsFound[i]);
			instCounter += opsFound[i];
		} 
	}

	printf("Total instructions found: %d \n", instCounter);
	printf("Total cycles found: %d \n", result);
	return result;
}

/* 
 * main driver of the program
 * add first argument as path for
 * any file you want to analyze.
 * returns result of estimator
 */
int main(int argc, char* argv[]){
	
	char* fileName = argv[1]; 	
	if(fileName == NULL){
		fileName = "barebones.s";
	}
	printf("Reading: %s \n", fileName);
	
	FILE* filePtr = openFile(fileName);
	int result = estimateFile(filePtr);
	
	fclose(filePtr);
	return result;

}
