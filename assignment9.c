#include <stdio.h> 
#include <string.h>
#define NAMEMAX 32

char namearray[4][NAMEMAX] = { 
"SMITH", 
"JOHNSON", 
"TANG", 
"ARCHER"
};

void printArr(){//prints array so you can see before and after
    for(int i = 0; i < 4; i++){
        printf("%d. %s\n", i, namearray[i]);
    }
}

void sort(){//bubble sort because I am lazy
    for(int i = 1; i < 4; i++){
        char tmp[NAMEMAX];
        if(strcmp(namearray[i], namearray[i-1]) < 0){
            strcpy(tmp, namearray[i]);
            strcpy(namearray[i], namearray[i-1]);
            strcpy(namearray[i-1], tmp);
        }
    }
    for(int i = 1; i < 4; i++){//just checks if sorted
        if(strcmp(namearray[i], namearray[i-1]) < 0){
            sort();
        }
    }
}

int search(char* input){//sequential search because i dont feel like doing recursion atm. also its a 4 element array
    for(int i = 0; i < 4; i++){
        if(strcmp(input, namearray[i])==0){
            return i;
        }
    }
    return -1;
}

int main() { 
    char input[NAMEMAX]; 
    int index; 
    int size = sizeof(namearray) / NAMEMAX;
    printf("UNSORTED ARRAY IS AS FOLLOWS\n");
    printArr();
    printf("\n\nSORTING...\n\n");
    sort(size, namearray);
    printf("SORTED!!!\n\nSHOWING SORTED ARRAY\n");
    printArr();
    while (1) { 
        printf("input last name: "); 
        scanf("%s", input); 
        if ((index = search(input)) < 0) { 
            printf("not found\n"); 
            continue;  
        } 
        printf("Found [%s] AT INDEX [%d]\n", namearray[index], index); 
    }     
}