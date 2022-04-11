#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	char input[256];
	if(argc < 2){
		printf("ERROR : USAGE => %s <string>\n", argv[0]);
		exit(0);
	}
	sprintf(input,"%s", argv[1]);
	char* backwards = (char*)malloc(strlen(input) * sizeof(char) + 1);
	int len = strlen(input);
	for(int i = len-1, ct = 0; i >= 0; i--){
		backwards[ct] = input[i];
		ct++;
	}
	printf("BACKWARDS => %s\n", backwards);
	printf("%s %s A PALINDROME\n", input, (strcmp(backwards, input)==0) ? "IS" : "ISN'T");
}
