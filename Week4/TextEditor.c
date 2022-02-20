#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char newText[2048];
char oldText[2048];
FILE* file;
int main(int argc, char* argv[]){
    if(argc < 2){
        printf("ERROR :Usage %s <filename>", argv[0]);
    }
    file = fopen(argv[1], "a+");
    while(fscanf(file, "%[^\n]", oldText) >0){
        fprintf(stdout, "%s\n", oldText);
    }
    //fseek(file, 0, SEEK_END);
    //long length = ftell(file);
    //oldText = malloc(length);
    //if(oldText){
    //    fread(oldText, 1, length, file);
    //}
    scanf("%[^\n]", newText);
    fprintf(file, "%s\n", newText);
    fclose(file);
}