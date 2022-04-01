#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* array;
int length = 0;

int binary_search(int index, int last, int item){
    if (last >= index) { 
        int mid = index + (last - index) / 2; 
        if (array[mid] == item) 
            return mid; 
        if (array[mid] > item) 
            return binary_search(index, mid - 1, item); 
        return binary_search(mid + 1, last, item); 
    } 
    return -1; 

}

void sort(){
    int notSorted = 0;
    for(int i = 1; i < length; i++){
        if(array[i] < array[i-1]){
            int tmp = array[i];
            array[i] = array[i-1];
            array[i-1] = tmp;
            notSorted = 1;
        }
    }
    if(notSorted){
        sort();
    }

}

void printArr(){
    for( int i = 0; i < length; i++){
        printf("%d. array[%d] = %d\n", i+1, i, array[i]);
    }
}

int main(){
    printf("Please input all your values, terminated by \"END\"\n");
    array = (int*)malloc(sizeof(int));
    char buf[24];
    scanf("%s", buf);
    while(!(strcmp(buf, "END")==0)){
        array[length] = atoi(buf);
        length++;
        array = (int*)realloc(array,sizeof(int)*(length+1));
        scanf("%s", buf);
    }
    sort();
    printf("Here is the sorted Array\n");
    printArr();
    printf("Type a value to search for : ");
    int item;
    scanf("%d", &item);
    int result = binary_search(0, length-1, item);
    if(result == -1){
        printf("%d WAS NOT IN THE ARRAY\n",item);
    }else{
        printf("%d WAS IN THE ARRAY AT INDEX %d\n", item, result);
    }
    free(array);

}