#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
    https://en.wikipedia.org/wiki/BMP_file_format
    USE THIS - ITS PRETTY EPIC
*/
#define HEADER_POS 14
#define WIDTH_POS 18
#define HEIGHT_POS 22
#define PIXEL_SIZE_POS 28

typedef struct{
    unsigned char b,g,r;
}pixel;


int getFileSize(FILE* file);
void blur(int row, int col, pixel img[row][col]);
void grey(int row, int col, pixel img[row][col]);
void rgb(char *cmd, int row, int col, pixel img[row][col]);

int main(int argc, char* argv[]){
    int row, col;
    FILE *in, *out;
    int Num_Rows, Num_Cols, Header;
    if(argc < 4){
        printf("usage : %s y|a# <imagefile> <outfile>\n", argv[0]);
        exit(0);
    }
    char *cmd = argv[1];
    in = fopen(argv[2], "r");
    if(in==(FILE*)NULL){
    //printf("GOTHEERE\n");
        printf("cannot open %s for reading\n", argv[2]);
    }
    out = fopen(argv[3], "w");
    if((out==(FILE*)NULL)){
        printf("cannot open %s for reading\n", argv[3]);
    }
    fseek(in, HEADER_POS, SEEK_SET);
    fread(&Header, 4, 1, in);
    printf("SIZE OF HEADER IS : %d BYTES\n", Header);
    fseek(in, WIDTH_POS, SEEK_SET);
    fread(&Num_Rows, 4, 1, in);
    printf("WIDTH OF IMAGE IS : %d PIXELS\n", Num_Rows);
    fseek(in, 22, SEEK_SET);
    fread(&Num_Cols, 4, 1, in);
    printf("HEIGHT OF IMAGE IS : %d PIXELS\n", Num_Cols);
    fseek(in, 28, SEEK_SET);
    int bitsPerPixel= 0;
    fread(&bitsPerPixel, 2, 1, in);
    printf("BYTES PER PIXEL : %d\n", bitsPerPixel/8);
    pixel img[Num_Rows][Num_Cols];
    fseek(in, Header, SEEK_SET);
    for(row = 0; row<Num_Rows;row++){
        fread(&img[row][0], Num_Cols, sizeof(pixel), in);
    }
    if(strchr(cmd, 'a') != (char*)NULL){
        int num = atol(cmd+1);
        blur(Num_Rows, Num_Cols, img);
    }else if (strchr(cmd, 'y')!=(char*)NULL){
        grey(Num_Rows, Num_Cols, img);
    }else if(strchr(cmd, 'r') != (char*)NULL ||
             strchr(cmd, 'g') != (char*)NULL ||
             strchr(cmd, 'b') != (char*)NULL){
        rgb(cmd, Num_Rows, Num_Cols, img);
    }else{
        printf("No valid comamnd in [%s]\n", cmd);
        exit(0);
    }
    char buf[128];
    fseek(in, 0, SEEK_SET);
    fread(buf, Header, 1, in);
    fwrite(buf, Header, 1, out);
    for(row = 0; row < Num_Rows; row++){
        fwrite(&img[row][0], Num_Cols, (bitsPerPixel/8), out);
    }
    fclose(in);
    fclose(out);
    printf("DONE!\n");
}

void rgb(char *cmd, int row, int col, pixel img[row][col]){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(strchr(cmd, 'r')!= (char*)NULL){
                img[i][j].r += 30;
            }
            if(strchr(cmd, 'g')!= (char*)NULL){
                img[i][j].g += 30;
            }
            if(strchr(cmd, 'b')!= (char*)NULL){
                img[i][j].b += 30;
            }
        }
    }
}

void grey(int row, int col, pixel img[row][col]){
    for(int i = 0; i < row; i ++){
        for(int j = 0; j < col;j++){
            pixel* p = &img[i][j];
            int px = p->r+p->g+p->b;
            px/=3;
            p->r = px;
            p->g = px;
            p->b = px;
        }
    }
}

void blur(int row, int col, pixel img[row][col]){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int r=0, b=0, g=0;
            long long ct=0;
            ct++;
            r+=img[i][j].r;
            g+=img[i][j].g;
            b+=img[i][j].b;
            if(i-1 >= 0 && j-1 >=0){
                r+=img[i-1][j-1].r;
                g+=img[i-1][j-1].g;
                b+=img[i-1][j-1].b;
                ct++;
            }
            else if(i-1 >= 0 && j+1 < col){
                r+=img[i-1][j+1].r;
                g+=img[i-1][j+1].g;
                b+=img[i-1][j+1].b;
                ct++;
            }
            else if(i+1 < row && j-1 >=0){
                ct++;
                r+=img[i+1][j-1].r;
                g+=img[i+1][j-1].g;
                b+=img[i+1][j-1].b;
            }
            else if(i+1 < row && j+1 <col){
                r+=img[i+1][j+1].r;
                g+=img[i+1][j+1].g;
                b+=img[i+1][j+1].b;
                ct++;
            }
            else if(i-1 >= 0){
                r+=img[i-1][j].r;
                g+=img[i-1][j].g;
                b+=img[i-1][j].b;
                ct++;
            }
            else if(j-1 >0){
                r+=img[i][j-1].r;
                g+=img[i][j-1].g;
                b+=img[i][j-1].b;
                ct++;
            }
            else if(i+1 < row){
                ct++;
                r+=img[i+1][j].r;
                g+=img[i+1][j].g;
                b+=img[i+1][j].b;
            }
            else if(j+1 < col){
                ct++;
                r+=img[i][j+1].r;
                g+=img[i][j+1].g;
                b+=img[i][j+1].b;
            }
            if(ct <= 0){ct=1;}
            img[i][j].r = (unsigned char)((r/ct)&0xFF);
            img[i][j].g = (unsigned char)((g/ct)&0xFF);
            img[i][j].b = (unsigned char)((b/ct)&0xFF);
        }
    }
}

int getFileSize(FILE* file){
    fseek(file, 0, SEEK_END);
    int end = ftell(file);
    rewind(file);
    return end;
}