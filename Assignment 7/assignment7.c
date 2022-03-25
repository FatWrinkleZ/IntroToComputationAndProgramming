#include <stdio.h>
#include <stdlib.h>
/*
    Threw out max value for a dynamic memory allocation version
*/
int is_sorted(int *array, int sz); 
int is_reverse(int *array, int sz); 
int in_array(int *array, int sz, int value);

int main() { 
    int* array;
    array = (int*)malloc(sizeof(int));//allocates the one int worth of memory to array
    int numItems = 0, input;
    printf("Please enter a set of integers, ending with -1.\n");
    scanf("%d", &input);//initial scan for input
    while(input != -1){//while end condition is false
        array[numItems] = input;//set current last index to input
        numItems++;//increment size of array
        array = (int*)realloc(array, (numItems+1)*sizeof(int));//allocate for next input
        scanf("%d", &input);//scan for another input
    }
    printf("There are %d input values and they are %s.\n", numItems,
    is_sorted(array, numItems) ? "sorted" : (is_reverse(array, numItems) !=0 ? "in reverse":"not sorted"));
    //prints stuff with ternary operators for descriptions
    printf("Please enter a search value.\n");
    scanf("%d", &input);
    printf("%s, %d was %s one of the input values\n", in_array(array, numItems, input) ? "Yes":"No", input, in_array(array,numItems,input)?"":"not");
    //prints stuff with ternary operators for descriptions
    free(array);//frees memory after array is used
}

int is_sorted(int *array, int sz){
    for(int i = 1; i < sz; i ++){
        if(array[i-1]>=array[i]){
            return 0;
        }
    }
    return 1;
}

int is_reverse(int *array, int sz){
    for(int i = sz-1; i>0;i--){
        if(array[i-1]<=array[i]){
            return 0;
        }
    }
    return 1;
}

int in_array(int *array, int sz, int value){
    for(int i = 0; i < sz; i++){
        if(array[i] == value){
            return 1;
        }
    }
    return 0;
}