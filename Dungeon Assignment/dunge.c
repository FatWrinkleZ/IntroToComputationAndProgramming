#include "mazeGenerator.h"
#include <math.h>	// in case you want abs()
#ifdef _WIN32
#include <conio.h>
#endif
#include <stdbool.h>
/*
-------THINGS TO CONSIDER IN CASE OF BUGS----------
> the maze is generated and allocated to memory at runtime
> I am parsing a 2D position from a 1D character array
> the macguffin, hidden door, locked door, and unlocked doors are generated along with maze generation
> program was written to also compile on windows as well and work with no extra code
*/

bool hideScreen=true;
// globals
int u_x=1, u_y=1;	// user x,y location on grid
int g_x=1, g_y=1;	// macguffin x,y location on grid (g for "goal")
FILE *fp;
char levelName[128];
int xSize = 0;
int ySize = 0;
int totalSize = 0;
int GoalPos = 0;
int pPos = 0;

// declaration of function prototypes
void save_state();
void refresh_screen();
void init(int, FILE*);
void leave_game(char *);
FILE* Level(int, char **);
void CheckForMovement(int, int);
void PlayLoop();
#define LINESIZ	96


int difficulty = 1;

char *MAP;

// movement controls -- feel free to redefine
#define MOV_N	'w'		// move North/Up
#define MOV_S	's'		// move South/Down
#define MOV_E	'd'		// move East/Right
#define MOV_W	'a'		// move West/Left
#define AMOV_N	'8'		// Alternative move North/Up
#define AMOV_S	'2'		// Alternative move South/Down
#define AMOV_E	'6'		// Alternative move East/Right
#define AMOV_W	'4'		// Alternative move West/Left
#define EXIT	'.'
#define mul 3

int selectDifficulty(){
	printf("What difficulty do you want to play at?\n EXHARD = 1, HARD = 2 , NORMAL = 2, EASY = 3, EXEASY = 4\n\tDIFFICULTY : ");
	int selection = 0;
	scanf("%d", &selection);
	if(selection >= 1 && selection<= 4){
		return selection;
	}
	printf("\nERROR : INPUT WAS NOT AN OPTION!\n");
	return selectDifficulty();
}


int main(int argc, char *argv[])
{
	#ifdef _WIN32
	printf("WINDOWS DETECTED : Setting Up With Windows Settings\n");
	#else
	printf("UNIX BASED SYSTEM DETECTED : SETTING UP WITH DEFAULTS\n");
	#endif
	char c;
	static const int x;
	static const int y;
	fp = Level(argc, argv);
	difficulty = selectDifficulty();
	init(argc, fp);
	PlayLoop();
}

void CheckForMovement(int dx, int dy){
	int playerPos = (u_x + ((xSize)*u_y));
	char TOMOVE = MAP[playerPos + dx + (dy*xSize)];
	if(TOMOVE == ' ' || TOMOVE=='%' || TOMOVE == '*' || TOMOVE == '$'){
		u_x+=dx;
		u_y+=dy;
	}
	if (abs(playerPos - GoalPos) <= 1) {
		leave_game("\n\n\tCongratulations! You found the MacGuffin!\n\n\n");
	}
}

void PlayLoop(){
	int playerPos = (u_x + ((xSize)*u_y));
	char input = 0;
	#ifdef _WIN32
	system("cls");
	refresh_screen();
	input = getch();
	#else
	system("clear");
	refresh_screen();
	input = getchar();
	#endif

		int dx = 0;
		int dy = 0;
	switch(input){
		case EXIT :	// save state and exit
			fp = fopen(levelName,"r+");
			leave_game("\nGood Bye.\n");
		break;
		case MOV_N:
			dy--;
			dx++;
		break;
		case MOV_E:
			dx++;
		break;
		case MOV_W:
			dx--;
		break;
		case MOV_S:
			dy++;
			dx--;
		break;
		case 'h':
		hideScreen = false;
		break;
		case '\n' : // newline -- ignore
			// do nothing
		break;
		default:
			printf("Error: Unrecognized input [%c]\n", input);
		break;
	}
	CheckForMovement(dx, dy);

	PlayLoop();
}

void save_state() 
{
	u_y = pPos/xSize;
	u_x = pPos%xSize+u_y;
	fp = fopen(levelName,"r+");
	rewind(fp);
	fprintf(fp, "%03d,%03d\n", u_x, u_y);
	printf("\rSAVED PLAYER POS (%03d, %03d) TO FILE", u_x, u_y);
	// write the current x,y coordinates of the user
	// to the first line of the file, in the form XXX,YYY
}

void refresh_screen()
{
	int playerPos = (u_x + ((xSize)*u_y));
	pPos = playerPos;
	int nextY = 0;
	for(int i = 0; i < totalSize; i++){
		if(MAP[i] == '\n'){nextY++;}
		int curY = (nextY);
		int curX = ((i%xSize)+nextY);
		int py = playerPos/xSize;
		int px = playerPos%xSize;
		if(abs(curX-px-py) <= difficulty*mul && abs(curY-u_y) <= difficulty*mul){
			if(i == playerPos){
				if(MAP[i-1] == '*' && MAP[i] == '*'){printf("[");printf("%c", '@');}
				else if(MAP[i+1] == '*' && MAP[i] =='*'){printf("@]");}
				else{printf("@");}
			}else if(i == GoalPos){printf("%c", '$');}
			else{
				switch(MAP[i]){
					case '\n':
					printf("\r");
					printf("\n");
					break;
					case '%':
					printf("+");
					break;
					case '*':
					if(MAP[i+1] == '*' && i+1 != playerPos){
						printf("[]");
						i++;
					}
					break;
					default:
					printf("%c", MAP[i]);
					break;
				}
			}
		}else{
			if(MAP[i] == '\n'){
				printf("\r");
				printf("\n");
			}else{printf("%c",' ');}
		}
	}
	//printf("\nSIZE = %d (X) & %d(Y) ----- TOTAL COUNT = %d", xSize, ySize, totalSize);
	//printf("\r\nGoal pos is : (%d, %d) ----- GLOBAL POS = %d\n", g_x, g_y, GoalPos);
}

void init(int argc, FILE* fp)
{
	if (fp == (FILE *)NULL) {
		printf("error: cannot open game file for reading\n");
		exit(0);
	}
	if (fscanf(fp, "%d,%d", &u_x, &u_y) != 2 || fscanf(fp, "%d,%d", &g_x, &g_y) != 2) {
		printf("error: file has incorrect header format\n");
		exit(0);
	}
	fprintf(stdout, "Init: Got user=[%d,%d] goal=[%d,%d]\n", u_x, u_y, g_x, g_y);
	char buf[10];
	int doneX = 0;
	int index = 0;
	MAP = (char*)malloc(sizeof(char));
	while(fscanf(fp, "%c", buf) > 0){
		if(doneX != 1){
			xSize++;
		}
		if(buf[0] == '\n' && index!=0){
			ySize++;
			doneX = 1;
		}
		MAP = (char*)realloc(MAP,sizeof(char) + index*sizeof(char));
		char buffer[2];
		sprintf(buffer, "%c", buf[0]);
		strcat(MAP, buffer);
		index++;
	}
	//xSize-=2;
	totalSize = index;
	printf("SIZE = %d (X) & %d(Y) ----- TOTAL COUNT = %d\n", xSize, ySize, totalSize);
	printf("%s", MAP);
	GoalPos = (g_y*xSize)+g_x;
	#ifdef _WIN32
	return;
	#endif
	system ("/bin/stty raw");
}

void leave_game(char *msg)
{
	save_state();
	free(MAP);
	fclose(fp);
	#ifndef _WIN32
	system ("/bin/stty cooked");
	#endif
	printf("%s", msg);
	exit(0);
}

FILE* Level(int argc, char *argv[]){
	FILE* level;
	int widthInt = 0;
	int heightInt = 0;
	printf("Would you like to play with a new maze? Or use an existing one?\n TYPE :\n 1 - For New Maze\n 2 - For Existing Maze\n");
	int option = 0;
	scanf("%d", &option);
	if(option == 1){
		char* argvs[4];
		argvs[0] = argv[0];
		printf("What do you want to call the level?\n");
		scanf("%s", levelName);
		argvs[1] = levelName;
		char width[4];
		printf("Type level width : ");
		scanf("%d", &widthInt);
		sprintf(width, "%d", widthInt);
		argvs[2] = width;
		char height[4];
		printf("Type level height : ");
		scanf("%d", &heightInt);
		sprintf(height, "%d", heightInt);
		argvs[3] = height;
		return InitializeMazeGen(4, argvs);
	}else if(option == 2){
		printf("What level do you want to load? : ");
		scanf("%s", levelName);
		level = fopen(levelName, "r");
	}else{
		printf("ERROR : UNRECOGNIZED INPUT!\n Trying Again...\n");
		return Level(argc, argv);
	}
	return level;
}
