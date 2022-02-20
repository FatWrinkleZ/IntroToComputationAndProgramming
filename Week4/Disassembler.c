#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char assemblyCode[256];

void parseInstruction(char* reg, int op, bool lastInd){//parses the hex key into an assembly registry/sim4
    char buffer[10];
    char strToAdd[10];
    sprintf(buffer, "%c", reg[0]);
    //short x = (short)strtol(buffer, NULL, 16);
    short int x;
    sscanf(buffer,"%X",&x);
    if(lastInd && (op==1 || op==7 || op==6 ||op == 5)){
        sprintf(strToAdd, "%d ", x);
    }else{
        sprintf(strToAdd, "r%d ", x);
    }
    strcat(assemblyCode, strToAdd);
}

int main(int argc, char *argv[]){
    if(argc <3){
        printf("USAGE : %s <machine file> <assembly output file>\n", argv[0]);
        exit(0);
    }
    FILE *inFile = fopen(argv[1],"r");
    FILE *outFile = fopen(argv[2], "w");
    if(inFile == (FILE*)NULL){
        printf("ERROR : cannot open %s for reading", argv[1]);
        exit(0);
    }
    char op[2], s1[2], s2[2], s3[2];
    int opAsHex;
    while(fscanf(inFile, "%c%c%c%c\n",op,s1,s2,s3)>0){
        assemblyCode[0] = '\0';//resets the string
        op[1] = s1[1] = s2[1] = s3[1] = '\0';
        //fprintf(stdout,"%s%s%s%s\n",op,s1,s2,s3);
        opAsHex = atoi(op);
        switch(opAsHex){
            case 0:
                strcat(assemblyCode, "ADD ");
            break;
            case 1:
                strcat(assemblyCode, "ADDI ");
            break;
            case 2:
                strcat(assemblyCode, "NAND ");
            break;
            case 3:
                strcat(assemblyCode, "OR ");
            break;
            case 4:
                strcat(assemblyCode, "MUL ");
            break;
            case 5:
                strcat(assemblyCode, "LW ");
            break;
            case 6:
                strcat(assemblyCode, "SW ");
            break;
            case 7:
                strcat(assemblyCode, "BNE ");
            break;
            default:
                printf("ERROR : Unrecognized opcode \"%c\"", op[0]);
                exit(0);
            break;

        }
        parseInstruction(s1, opAsHex, false);
        parseInstruction(s2, opAsHex, false);
        parseInstruction(s3, opAsHex, true);
        fprintf(stdout, "GOT : 0x%c%c%c%c - %c %c %c %c - %s\n",op[0],s1[0],s2[0],s3[0],op[0],s1[0],s2[0],s3[0], assemblyCode);
        fprintf(outFile, "%s\n",assemblyCode);
    }
    fclose(inFile);
    fclose(outFile);
}