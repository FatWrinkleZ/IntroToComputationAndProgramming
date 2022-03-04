#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
    bool hasPassword = false;
    int attempt = 1;
    char password[] = "super321Password";
    char input[128];
    while(attempt <= 5){
        printf("ATTEMPTS REMAINING %d ||||||| Input Password : ", 6 - attempt);
        scanf("%s", input);
        if(strcmp(password, input) == 0){
            hasPassword = true;
            break;
        }
        attempt++;
    }
    if(hasPassword){
        printf("You got the password\n");
        return 0;
    }
    printf("You messed up all attempts\n");
}