#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// in case you want strlen()
#include <math.h>	// in case you want abs()
#ifdef WIN32
#include <conio.h>
#endif

// globals
int u_x=1, u_y=1;	// user x,y location on grid
int g_x=1, g_y=1;	// macguffin x,y location on grid (g for "goal")
int max_x, max_y;	// the bounds of the floorplan, determined from input file
FILE *fp;

// declaration of function prototypes
void save_state();
void refresh_screen();
void init(int, char **);
void leave_game(char *);

#define LINESIZ	96

// movement controls -- feel free to redefine
#define MOV_N	'8'		// move North/Up
#define MOV_S	'2'		// move South/Down
#define MOV_E	'6'		// move East/Right
#define MOV_W	'4'		// move West/Left
#define AMOV_N	'w'		// Alternative move North/Up
#define AMOV_S	'x'		// Alternative move South/Down
#define AMOV_E	'd'		// Alternative move East/Right
#define AMOV_W	'a'		// Alternative move West/Left
#define EXIT	'.'

int main(int argc, char *argv[])
{
	#ifdef WIN32
	printf("WINDOWS DETECTED : Setting Up With Windows Settings\n");
	#else
	printf("UNIX BASED SYSTEM DETECTED : SETTING UP WITH DEFAULTS\n");
	#endif

	char c;

	init(argc, argv);

	while (1) {
		refresh_screen();
		char c;
		#ifdef WIN_32
		c = getch();
		#else
		c = getchar();
		#endif
		switch (c) {

			// handle movement
			// for each direction, handle its effects
			// allow both the regular and ALT move inputs

			case EXIT :	// save state and exit
				save_state();
				leave_game("\nGood Bye.\n");
			break;

			case '\n' : // newline -- ignore
				// do nothing
			break;

			default:
				printf("Error: Unrecognized input [%c]\n", c);
			break;
		}
		if (g_x == u_x && g_y == u_y) {
			leave_game("\n\n\tCongratulations! You found the MacGuffin!\n\n\n");
		}
	}
}

void save_state() 
{
	// write the current x,y coordinates of the user
	// to the first line of the file, in the form XXX,YYY
}

void refresh_screen()
{
	char buf[LINESIZ];
	int i;

	rewind(fp);
	printf("\n");
	fgets(buf, LINESIZ, fp);	// skip first line
	fgets(buf, LINESIZ, fp);	// skip second line
	for (i=0; fgets(buf, LINESIZ, fp); i++) {
		// print the line to the screen
		// if the player is there, overlay the '@' symbol
		// if the magguffin is within 2 spaces of the user, print it as well
	}
}

void init(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: %s <map file>\n", argv[0]);
		exit(0);
	}

	fp = fopen(argv[1], "r+");

	if (fp == (FILE *)NULL) {
		printf("error: cannot open game file %s for reading\n", argv[1]);
		exit(0);
	}
	if (fscanf(fp, "%d,%d", &u_x, &u_y) != 2 || fscanf(fp, "%d,%d", &g_x, &g_y) != 2) {
		printf("error: file %s has incorrect header format\n", argv[1]);
		exit(0);
	}
	fprintf(stderr, "Init: Got user=[%d,%d] goal=[%d,%d]\n", u_x, u_y, g_x, g_y);

	#ifdef WIN32
	return;
	#endif
	system ("/bin/stty raw");
}

void leave_game(char *msg)
{
	fclose(fp);
	#ifdef WIN32
	#else
	system ("/bin/stty cooked");
	#endif
	printf("%s", msg);
	exit(0);
}
