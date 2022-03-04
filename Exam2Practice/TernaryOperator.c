#include <stdio.h>

int main(){
    int a = 1, b = 5, c = 6, d = 3;
    char output[20];
    sprintf(output,"%s", (c % d == 0) ? "are" : "aren't");
    printf("They %s divisible\n", output);
}