#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numStudents = 0;

enum {
	MAJ_CE = 0,
	MAJ_CS,
	MAJ_EE,
	MAJ_MA,
	MAJ_ME,
	MAJ_PH,
};

char *majors[] = {
	"Computer Engineering",
	"Computer Science",
	"Electrical Engineering",
	"Mathematics",
	"Mechanical Engineering",
	"Physics",
};

char *years[] = {
	"Freshman",
	"Sophomore",
	"Junior",
	"Senior",
	"5th Year Senior",
	"6th Year Senior",
};

#define FIELD	64
typedef struct student {
	char lname[FIELD];
	char fname[FIELD];
	int UID;
	int year;
	int major;
}student;

student *st_array;
/*
	{	"Jones",	"Jennie",	293874, 2, MAJ_EE },
	{	"Smith",	"Sean",		394857, 0, MAJ_CS },
	{	"Anderson",	"Andrea",	878767, 1, MAJ_CE },
	{	"Johnson",	"John",		876874, 3, MAJ_MA },
	{	"Jackson",	"Jack",		983457, 2, MAJ_ME },
	{	"Clarkson",	"Chloe",	234567, 1, MAJ_PH }
*/
void search_lname(char * name);
void search_fname(char * name);
void search_uid(int num);
void search_year(int num);
void search_major(int num);
void create_student(char *lname, char *fname, int uid, int year, int major);
void print_array();
void print_student(int numFound, int index, int isSearching);
char* major_to_str(int major);
void generateInitialStudents(){
	st_array = (student*)malloc(sizeof(student)*1);
	create_student("Jones", "Jennies", 293874, 2, MAJ_EE);
	create_student("Smith", "Sean", 394857, 0, MAJ_CS);
	create_student("Anderson", "Andrea", 878767, 1, MAJ_CE);
	create_student("Johnson", "John", 876874, 3, MAJ_MA);
	create_student("Jackson", "Jack", 983457, 2, MAJ_ME);
	create_student("Clarkson", "Chloe", 234567, 1, MAJ_PH);
}


int main(int argc, char *argv[]) {
	char userinput[4*FIELD];
	char *input, *lname, *fname;
	int uid, year, major;
	char cmd;
	generateInitialStudents();
	print_array();

	while (1) {
		printf("\nPlease enter a command (\'l,f,u,y,m,i,a\' LNAME|FNAME|UID|YR(#)|MAJ(#)).\n>");
		scanf("%[^\n]", userinput);
		cmd = userinput[0];
		// skips over all spaces and/or commas
		input = strtok(userinput+1, " ,");
		switch (cmd) {

			case 'l':
				printf("Printing all students matching last name [%s] …\n", input);
				search_lname(input);
				break;

			case 'f':
				printf("Printing all students matching first name [%s] …\n", input);
				search_fname(input);
				break;

			case 'u':
				printf("Printing all students matching UID [%s] …\n", input);
				search_uid(atoi(input));
				break;

			case 'y':
				printf("Printing all students matching year [%s] ...\n", input);
				search_year(atoi(input));
				break;

			case 'm':
				printf("Printing all students matching major [%s] ...\n", input);
				search_major(atoi(input));
				break;

			case 'i':
				lname = input;
				fname = strtok(NULL, ", ");
				uid = atoi(strtok(NULL, ", "));
				year = atoi(strtok(NULL, ", "));
				major = atoi(strtok(NULL, ", "));
				printf("inserting %s,%s,%d,%d,%d\n", lname, fname, uid, year, major);
				create_student(lname, fname, uid, year, major);
				break;

			case 'a':
				printf("Printing database ...\n");
				print_array(st_array);
				break;

			case '.':
				free(st_array);
				exit(0);
				break;

			default:
				printf("bad command [%c]\n", cmd);
				break;
		}
		scanf("%c", &cmd);
	}
}

char* major_to_str(int major){
	switch(major){
		case MAJ_CE:
		return "Computer Engineering";
		break;
		case MAJ_CS:
		return "Computer Science";
		break;
		case MAJ_EE:
		return "Electrical Engineering";
		break;
		case MAJ_MA:
		return "Master of Arts";
		break;
		case MAJ_ME:
		return "Mechanical Engineering";
		break;
		case MAJ_PH:
		return "Physics";
		break;
		default:
		return "NULL (NOT FOUND IN MAJOR LIST)";
		break;
	}
}

void print_array(){
	for(int i = 0; i < numStudents;i++){
		print_student(i+1, i, 0);
	}
}

void print_student(int numFound, int index, int isSearching){
	printf("\n%d. %s\n\tNAME : %s %s\n\tUID : %d\n\tYEAR : %d\n\tMAJOR : %s\n", numFound, (isSearching == 1) ? "FOUND STUDENT : ":"",
		st_array[index].fname, st_array[index].lname, st_array[index].UID, st_array[index].year, major_to_str(st_array[index].major));
}

void search_lname(char * name){
	int numFound = 0;
	for(int i = 0; i < numStudents;i ++){
		if(strcmp(name, st_array[i].lname)==0){
			numFound++;
			print_student(numFound, i, 1);
		}
	}
	if(numFound == 0){printf("COULD NOT FIND ANY STUDENTS WITH LAST NAME - [%s]\n", name);}
}
void search_uid(int uid){
	int numFound = 0;
	for(int i = 0; i < numStudents;i ++){
		if(uid == st_array[i].UID){
			numFound++;
			print_student(numFound, i, 1);
		}
	}
	if(numFound == 0){printf("COULD NOT FIND ANY STUDENTS WITH UID - [%d]\n", uid);}
}
void search_major(int major){
	int numFound = 0;
	for(int i = 0; i < numStudents;i ++){
		if(major == st_array[i].major){
			numFound++;
			print_student(numFound, i, 1);
		}
	}
	if(numFound == 0){printf("COULD NOT FIND ANY STUDENTS WITH MAJOR - [%s]\n", major_to_str(major));}
}
void search_year(int year){
	int numFound = 0;
	for(int i = 0; i < numStudents;i ++){
		if(year == st_array[i].year){
			numFound++;
			print_student(numFound, i, 1);
		}
	}
	if(numFound == 0){printf("COULD NOT FIND ANY STUDENTS IN THEIR [%d] YEAR\n", year);}
}

void search_fname(char * name){
	int numFound = 0;
	for(int i = 0; i < numStudents;i ++){
		if(strcmp(name, st_array[i].fname)==0){
			numFound++;
			print_student(numFound, i, 1);
		}
	}
	if(numFound == 0){printf("COULD NOT FIND ANY STUDENTS WITH FIRST NAME - [%s]\n", name);}
}

void create_student(char *lname, char *fname, int uid, int year, int major){
	sprintf(st_array[numStudents].lname, "%s", lname);
	sprintf(st_array[numStudents].fname,"%s", fname);
	st_array[numStudents].UID = uid;
	st_array[numStudents].year = year;
	st_array[numStudents].major = major;
	numStudents++;
	st_array = (student*)realloc(st_array, (numStudents+1)*sizeof(student));

}