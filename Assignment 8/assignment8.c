#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* array;
int length = 0;

int binary_search(int index, int last, int item){//searches by getting the midpoint between its last point and current point based 
                                                 //on if current value is greater than or less than item of interest
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

void sort(){//sorts by swapping values that are not in order
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

void printArr(){//prints array
    for( int i = 0; i < length; i++){
        printf("%d. array[%d] = %d\n", i+1, i, array[i]);
    }
}

int main(){
    printf("Please input all your values, terminated by \"END\"\n");
    array = (int*)malloc(sizeof(int));//allocates 1 int worth of memory to array
    char buf[24];
    scanf("%s", buf);
    while(!(strcmp(buf, "END")==0)){
        array[length] = atoi(buf);
        length++;
        array = (int*)realloc(array,sizeof(int)*(length+1));//allocates new int to array
        scanf("%s", buf);
    }
    sort();//run sort function
    printf("Here is the sorted Array\n");
    printArr();//run print function
    printf("Type a value to search for : ");
    int item;
    scanf("%d", &item);//intake item to search for
    int result = binary_search(0, length-1, item);//run binary search with initial conditions
    if(result == -1){//check if item was not in array
        printf("%d WAS NOT IN THE ARRAY\n",item);
    }else{//print index that item was found in
        printf("%d WAS IN THE ARRAY AT INDEX %d\n", item, result);
    }
    free(array);//free the memory allocated to array

}