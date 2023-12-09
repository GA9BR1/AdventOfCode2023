#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    
    int sum = 0;
    char buffer;
    char concat[3];
    char firstDigit = ' ';
    char lastDigit;

    while(fread(&buffer, 1, 1, fp)) {
        if(isdigit(buffer)){
            if(firstDigit == ' ') {
                firstDigit = buffer;
                lastDigit = buffer;
            } else {
                lastDigit = buffer;
            }
        }
        
        if(buffer == '\n'){
            concat[0] = firstDigit;
            if(lastDigit != '\0'){
                concat[1] = lastDigit;
            } else {
                concat[1] = firstDigit;
            }
            concat[2] = '\0';
            int num = atoi(concat);
            sum += num;
            firstDigit = ' ';
            lastDigit = '\0';          
        }
    }
    printf("%i", sum);
}