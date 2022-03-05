#include <stdio.h>

int main(){
    int a = 1, b = 5, c = 6, d = 3;
    printf("They %s divisible\n", (c % d == 0) ? "are" : "aren't");
}