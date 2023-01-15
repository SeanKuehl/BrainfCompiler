#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc == 2){
		printf("%s\n", argv[1]);  //first argv is program name
    
	}
	char code[10000];
	int codeIndex = 0;

	int instructionPointer = 0;
	int cells[3000] = {0};
	int cellPointer = 0;

	char ch;
	FILE *file;
	file = fopen(argv[1],"r");
  
	if(file == NULL)
	{
		printf("Error!");   
		exit(1);             
	}

	while (!feof(file)) {
		ch = fgetc(file);
		code[codeIndex] = ch;
		codeIndex++;
	}
	//add ending char
	code[codeIndex] = ';';
	int indexOfLastStartLoop = 0;
	char input = ' ';
	
	bool done = false;
	while (done == false){
		
		char currentCommand = code[instructionPointer];
		
		
		switch (currentCommand){
		case '+':
			cells[cellPointer] += 1;
			break;
		case '-':
			cells[cellPointer] -= 1;
			break;
		case '<':
			cellPointer -= 1;
			break;
		case '>':
			cellPointer += 1;
			break;
		case '[':
			//if current val is 0, end loop. Otherwise start it
			indexOfLastStartLoop = instructionPointer;
			if (cells[cellPointer] == 0){
				for (int i = instructionPointer+1;i<10000;i++){
					if (code[i] == ']'){
						instructionPointer = i + 1;
						break;
					}
				}
			}
			
			break;
		case ']':
			//if current val != 0, restart loop, otherwise end of loop
			if (cells[cellPointer] != 0){
				//restart the loop
				instructionPointer = indexOfLastStartLoop -1;	//this is to counteract the always incrementing pointer
			}
			else {
				//do nothing, end loop
			}
			break;
		case '.':
			//output ascii val of active cell
			printf("%c", (char)(cells[cellPointer]));
			break;
		case ',':
			//store val of char entered into current cell
			input = getc(stdin);
			cells[cellPointer] = (int)(input);
			break;
		case ';':
			//we've reached the end of the code
			done = true;
			break;
		default:
			break;
		}
		instructionPointer++;
	}

	
	
			
	

	fclose(file);
  
  
	return 0;
}