#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

FILE* getFile();

typedef struct {
	int sPos;
	int num;
	bool founded;
} numPos;

numPos getFirstWord(char *line, int i);
numPos getFirstDigit(char *line);
numPos getLastWord(char *line, int i);
numPos getLastDigit(char *line);

char *numberWords[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char *numberWordsReversed[] = {"eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin"};

int main() 
{
	FILE *fp = getFile();
	int x = 0;
	char *line;
	size_t tamanho = 0;
	int count = 0;
	int sum = 0;
	char concat[3];


	while (getline(&line, &tamanho, fp) != -1) {

		int realFirstNum = 0;
		int realLastNum = 0;

		numPos firstDigit;
		numPos firstWord;
		firstDigit.founded = false;
		firstDigit.sPos = 0;
		firstWord.founded = false;
		firstWord.sPos = 0;

		numPos lastDigit;
		numPos lastWord;
		lastDigit.founded = false;
		lastDigit.sPos = 0;
		lastWord.founded = false;
		lastWord.sPos = 0;

		firstDigit.num = 0;
		firstWord.num = 0;

		lastDigit.num = 0;
		lastWord.num = 0;

		for(int i = 0; i < 9; i++){
			// First Word
			numPos tmpFirst = getFirstWord(line, i);
			if(firstWord.founded == false){
				firstWord = tmpFirst;
			}
			else if(tmpFirst.sPos < firstWord.sPos){
				firstWord = tmpFirst;
			}
			//

			// Last Word
			numPos tmpLast = getLastWord(line, i);
			if(lastWord.founded == false){
				lastWord = tmpLast;
			}
			else if(tmpLast.sPos < lastWord.sPos){
				lastWord = tmpLast;
			}
			//
		}

		// First digit and first real digit
		firstDigit = getFirstDigit(line);
		if(firstDigit.founded == true || firstWord.founded == true) {
			if(firstWord.sPos < firstDigit.sPos){
				realFirstNum = firstWord.num;
			} else {
				realFirstNum = firstDigit.num;
			}
			realLastNum = realFirstNum;
		}
		// Last digit and last real digit
		lastDigit = getLastDigit(line);
		if(lastDigit.founded == true || lastWord.founded == true) {
			if(lastWord.sPos < lastDigit.sPos){
				realLastNum = lastWord.num;
			} else {
				realLastNum = lastDigit.num;
			}
		}
		//

		concat[0] = realFirstNum + '0';
		concat[1] = realLastNum + '0';
		concat[2] = '\0';
		sum += atoi(concat);
    }
	printf("%i", sum);
}

numPos getLastWord(char *line, int i) {
	char reversed[strlen(line)];
	int x;
	numPos result;
	int c = 0;

	for (int j = strlen(line) - 1; j >= 0; j--) {
		reversed[c++] = line[j];
	}
	reversed[c] = '\0';

	char *founded = strstr(reversed, numberWordsReversed[i]);
	if(founded != NULL) {
		x = founded - reversed;
		result.sPos = x;
		result.num = i + 1;
		result.founded = true;
	} else {
		result.sPos = 999;
	}

	return result;
}

numPos getLastDigit(char *line) {
	char reversed[strlen(line)];
	numPos result;
	int c = 0;

	for (int i = strlen(line) - 1; i >= 0; i--) {
		reversed[c++] = line[i];
	}
	reversed[c] = '\0';

	for(int i = 0; i < strlen(reversed); i++)
	{
		if(isdigit(reversed[i])){
			result.sPos = i;
			result.num = (int)(reversed[i] - '0');
			result.founded = true;
			break;
		}
	}

	return result;
}

numPos getFirstWord(char *line, int i) {
	int x;
	numPos result;


	char *founded = strstr(line, numberWords[i]);
	if(founded != NULL) {
		x = founded - line;
		result.sPos = x;
		result.num = i + 1;
		result.founded = true;
	} else {
		result.sPos = 999;
	}
	
	return result;
}

numPos getFirstDigit(char *line) {
	numPos result;

	for(int i = 0; i < strlen(line); i++)
	{
		if(isdigit(line[i])){
			result.sPos = i;
			result.num = (int)(line[i] - '0');
			result.founded = true;
			break;
		}
	}
	
	return result;
}

FILE* getFile()
{
    FILE *fp = NULL;
    
    errno = 0;
    fp = fopen("entry.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening %s for reading, errno: %d\n", "entry.txt", errno);
        exit(1);
    } else {
        return fp;
    }
}