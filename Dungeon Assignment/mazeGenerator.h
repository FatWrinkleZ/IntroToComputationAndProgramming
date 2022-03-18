#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifdef WIN_32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define MAX_GOAL_ITTERATIONS 1028

void CarveMaze(char *maze, int width, int height, int x, int y) {

   int x1, y1;
   int x2, y2;
   int dx, dy;
   int dir, count;
   int MaggufinPosx, MaggufinPosy;
   dir = rand() % 4;
   count = 0;
   while(count < 4) {
      dx = 0; dy = 0;
      switch(dir) {
      case 0:  dx = 1;  break;
      case 1:  dy = 1;  break;
      case 2:  dx = -1; break;
      default: dy = -1; break;
      }
      x1 = x + dx;
      y1 = y + dy;
      x2 = x1 + dx;
      y2 = y1 + dy;
      if(   x2 > 0 && x2 < width && y2 > 0 && y2 < height
         && maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {
         maze[y1 * width + x1] = 0;
         maze[y2 * width + x2] = 0;
         x = x2; y = y2;
         dir = rand() % 4;
         count = 0;
      } else {
         dir = (dir + 1) % 4;
         count += 1;
      }
   }

}


void SpawnGoal(char* maze, int width, int height, int* gx, int* gy, int itteration){
   #ifdef WIN_32
   Sleep(1);
   #else
   usleep(10);
   #endif
   int totalSize = (width*height) + height-(width*3);
	srand(time(0));
	int x = width+(rand()%(totalSize));
	int yPos = x/width;
	int xPos = x%(width);
   //positions[0] = yPos;
   //positions[1] = xPos;
	x-= 2;
   int tempInd = (xPos + (yPos * (width)));
	while(((x < 0 && x > totalSize) && (maze[tempInd] == 1)) /*|| itteration >= MAX_GOAL_ITTERATIONS*/){
      x = width + (rand()%totalSize);
      yPos = x/width;
      xPos = x%width;
      printf("\rSPAWNING GOAL... => ITTERATION %d => CURRENT MPOS IS (%d,%d) AT IND %d",itteration, xPos, yPos, x);
	      //return x;
	}
   itteration++;
         *gx=xPos;
         *gy=yPos;
	//return SpawnGoal(maze, width, height, gx, gy, itteration);

}

void GenerateMaze(char *maze, int width, int height) {
   srand(time(0));
   int x, y;
   for(x = 0; x < width * height; x++) {
      maze[x] = 1;
      int r = rand()%100 + 1;

      if(r % 80 == 0){
         maze[x] =4;
      }
      if(r%60 == 0){
         maze[x] =3;
      }
      if(r % 70 == 0){
         maze[x] = 2;
      }
   }
   maze[1 * width + 1] = 0;
   
   for(y = 1; y < height; y += 2) {
      for(x = 1; x < width; x += 2) {
         CarveMaze(maze, width, height, x, y);
      }
   }
   maze[0 * width + 1] = 0;
   maze[(height - 1) * width + (width - 2)] = 0;
}

void BUILD_WALLS(char* maze, int width, int height){
   for(int i = 0; i < strlen(maze);i++){
      if(i % width-1 == 0  || i % width -2 == 0 || i >= (height-1)*width){
         maze[i] == '[';
         maze[i+1] == ']';
      }
   }
}

FILE* SerializeMaze(char *maze, int width, int height, char* argv1){
    FILE* file = fopen(argv1, "w");
    //printf("Erroring Here");
   GenerateMaze(maze , width, height);
   int x, y;
   int gx, gy;
   BUILD_WALLS(maze, width, height);
   SpawnGoal(maze, width, height, &gx, &gy, 0);
   fprintf(file, "002,001\n%03d,%03d\n", gx,gy);
   for(y = 0; y < height; y++) {
      for(x = 0; x < width; x++) {
         switch(maze[y * width + x]) {
         case 1:  fprintf(file, "[]");  break;
         case 2: fprintf(file, "**"); break;
         case 3: fprintf(file, "++"); break;
         case 4: fprintf(file, "%%");fprintf(file, "%%"); break;
         default: 
         fprintf(file, "  ");  
         break;
         }
      }
      fprintf(file, "\n");
      
   }
   fclose(file);
   file = fopen(argv1, "r");
   return file;
}

FILE* InitializeMazeGen(int argc, char* argv[]){
    int width, height;
    char *maze;

    if(argc < 4){
        printf("USAGE : %s <mazefile> <width> <height>" ,argv[0]);
        exit(0);
    }
    //printf("STATS , (%s, %s)", argv[2], argv[3]);
    sscanf(argv[2], "%d", &width);
    sscanf(argv[3], "%d", &height);
    maze = (char*)malloc(width * height * sizeof(char));
    //char path[256] = "LEVELS/";
    //strcat(path, argv[1]);
    printf("STATS , (%d, %d)\n", width, height);
    FILE* file = SerializeMaze(maze, width, height, argv[1]);
    //fclose(file);
    return file;
}
