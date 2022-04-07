#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE* f;
    f = fopen(argv[1], "r");
    int info=0;
    fseek(f, 14, SEEK_SET);
    fread(&info, 4, 1, f);
    printf("SIZE OF HEADER IS : %d BYTES\n", info);
    fseek(f, 18, SEEK_SET);
    fread(&info, 4, 1, f);
    printf("WIDTH OF IMAGE IS : %d PIXELS\n", info);
    fseek(f, 22, SEEK_SET);
    fread(&info, 4, 1, f);
    printf("HEIGHT OF IMAGE IS : %d PIXELS\n", info);
    fseek(f, 28, SEEK_SET);
    fread(&info, 2, 1, f);
    printf("BYTES PER PIXEL : %d\n", info/8);
}