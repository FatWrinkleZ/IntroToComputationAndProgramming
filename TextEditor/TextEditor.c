#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif
#include <string.h>

int main(int argc, char* argv[]){
    #ifdef _WIN32
    printf("WINDOWS SYSTEM DETECTED\n");
    #else
    WINDOW* screen = initscr();//ncurses method to have a mini window of its own(kinda, still in terminal)
    #endif
    char inFileName[32];//stores the file name
    if(argc > 1){
        sprintf(inFileName, "%s",argv[1]);
    }else{
        #ifdef _WIN32
        printf("What File do you want to edit - ");
        scanf("%s", inFileName);
        #else
        printw("What File do you want to edit? - ");//asks for file to edit
        scanw("%s", inFileName);//places user input into the inFileName string
        #endif
    }
    FILE* file = fopen(inFileName, "r");//opens the file for reading
    #ifdef _WIN32
    system("cls");
    #else
    clear();//clears whatever is on the screen
    #endif
    char* fileContent = malloc(20 * sizeof(char)); //allocates 20 characters worth of memory to fileContent
    fileContent[0] = '\0';//sets the initial index of fileContent to the end of the string
    char buffer[2];//creates a small character array to hold 1 character of the file content at a time
    int numCharacters = 20;//index to keep track of length of file content
    if(file != (FILE*)NULL){//if the file exists
        while(fscanf(file, "%c", buffer)>0){//puts the entire file content into a string
            fileContent = (char*)realloc(fileContent, numCharacters * sizeof(char)); // expands to amount of memory allocated by 1 character
            char veryTemp[2];//creates very temp string that is meant to store only the first index of buffer
            sprintf(veryTemp, "%c", buffer[0]);//prints content to string
            strcat(fileContent, veryTemp);//concatenates content to a string
            numCharacters++;//increments character length count
        }
    }
    file = fopen(inFileName, "w");//opens file for writing (clearing its contents)
    char input = 0;//sets the initial value of the input character to the NULL character
    #ifdef _WIN32
    printf("%s", fileContent);
    #else
    printw("%s", fileContent);//prints the file content to the screen
    #endif
    while(input != 0x1B){//while escape is not the key that is pressed
        #ifdef _WIN32
        input = getch();
        system("cls");
        #else
        input = wgetch(screen);//ncurses function that gets key press
        clear();//ncurses function that clears the screen
        #endif
        char buf[10];//holds the input character as a string to be concatenated later
        if(input == 0x7f){ //if it is the backspace hex key
            numCharacters--;//decrements numCharacters by 1
            fileContent[strlen(fileContent)-1] = '\0';//makes the end of the string (current length - 1)
            fileContent = (char*)realloc(fileContent, numCharacters * sizeof(char));//reduces the amount of memory allocated by 1 character
        }else if (input != 0x1B && (input > 13||input == '\n')){
            numCharacters++;//increments numCharacters by 1
            fileContent = (char*)realloc(fileContent, numCharacters * sizeof(char));//expands the amount of memory allocated by 1 character
            sprintf(buf, "%c", input);//makes buff contain the input character
            strcat(fileContent, buf);//concatenates the buf string to the total contents
        }
        #ifdef _WIN32
        printf("%s", fileContent);
        #else
        printw("%s",fileContent);//prints the entire string
        #endif
    }
    fileContent[numCharacters] = '\0';//makes the end of the file before the escape key was pressed
    fprintf(file, "%s", fileContent);//prints fileContent to the file
    fclose(file);//closes the file
    free(fileContent);//frees the memory allocated to fileContent
    #ifndef _WIN32
    endwin();//closes the ncurses window
    #endif
    printf("Successfully saved %d characters to file\n", numCharacters-20);
}