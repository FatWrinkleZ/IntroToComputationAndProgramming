#include <stdio.h>
#include <stdlib.h>

int main(){
    int amt = 0;
    int currentCount = 0;
    int index = 0;
    printf("Enter amount of even numbers - ");
    scanf("%d", &amt);
    while(currentCount < amt){
        index++;
        if(index%2 == 0){
            printf("%d,",index);
            currentCount++;
        }
    }
    printf("\nEXITING\n");
}