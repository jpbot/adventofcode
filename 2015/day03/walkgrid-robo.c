#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>

#define ERRDEBUG 0
#define ERRINFO 1
#define ERRWARN 2
#define ERRERROR 3
#define ERRFATAL 4

#define INFILEARG 1
#define DEFAULTINPUTFILE "input_day03.in"

#define START 0
#define NORTH 1
#define WEST  2
#define EAST  3
#define SOUTH 4

static int logf(int level, char *fmt, ...);
static void usage(char *programName);
int scan_instructions(FILE *infile, void dir_execute(int, int *, int), int *grid, int maxlen);
static void show_direction(int direction, int *grid, int maxlen);
static void * i2db_init(int maxlen);
static int i2db_put(void *map, int maxlen, int x, int y, int val);
static int i2db_get(void *map, int maxlen, int x, int y, int *val);

int main(int argc, char **argv){
   int searchfloor = 0;
   int instruction_step = 0;
   char *inputfile = 0;
   char instruction = 0;
   FILE *infile;
   int *grid;

   int filesz;
   struct stat stbuf;
   int fd;

   if(argc < INFILEARG + 1){   //set default file
      inputfile = malloc(strlen(DEFAULTINPUTFILE) + 1);
      if(!inputfile){
         logf(ERRFATAL, "couldn't allocate memory for input file name.");
         return EXIT_FAILURE;
      }
      strcpy(inputfile, DEFAULTINPUTFILE);
   } else {
      inputfile = argv[INFILEARG];
   }
   logf(ERRINFO, "Input file: %s", inputfile);

   infile = fopen(inputfile, "r");
   if(!infile){
      logf(ERRFATAL, "could not open file %s for input. Cannot continue.", inputfile);
      return EXIT_FAILURE;
   }

   // open the file a second time just so we can see how long the file is
   fd = open(inputfile, O_RDONLY);
   if(fd == -1){
      logf(ERRFATAL, "could not open file %s for input. Cannot continue.", inputfile);
      return EXIT_FAILURE;
   }

   if((fstat(fd, &stbuf) != 0) || (!S_ISREG(stbuf.st_mode))) {
      logf(ERRFATAL, "could not stat file %s, or %s in not a regular file. Cannot continue.", inputfile);
   }

   filesz = stbuf.st_size;
   logf(ERRINFO, "file %s is %d bytes.", inputfile, filesz);
   close(fd);

   grid = i2db_init(filesz);
   show_direction(START, grid, filesz);
   scan_instructions(infile, show_direction, grid, filesz);

   return EXIT_SUCCESS;
}

static void * i2db_init(int maxlen){
   // allocate the memory for 2d int map
   void *map = 0;

   map = malloc(((maxlen * 2) * (maxlen * 2 + 1) + 1) * sizeof(int));
   if(map)
      memset(map, 0, ((maxlen * 2) * (maxlen * 2 + 1) + 1) * sizeof(int));

   logf(ERRDEBUG, "        map: %d", map);
   logf(ERRDEBUG, "     maxlen: %d", maxlen);
   logf(ERRDEBUG, "sizeof(int): %d", sizeof(int));
   logf(ERRDEBUG, "        max: %d", ((maxlen * 2) * (maxlen * 2 + 1) + 1));

   return map;
}

static int i2db_add(void *map, int maxlen, int x, int y, int val){
   size_t index = 0;
   int *map_val = 0;

   if(x < 0)  x = x * -1 + maxlen;
   if(y < 0)  y = y * -1 + maxlen; 
   index = x * maxlen * 2 + y;
   map_val = map + index * sizeof(int);
   
   if(index > (maxlen * 2) * (maxlen * 2 + 1)  + 1){
      logf(ERRDEBUG, "index: %d", index);
      logf(ERRDEBUG, "  max: %d", ((maxlen * 2) * (maxlen * 2 + 1) + 1));
      logf(ERRFATAL, "Attempt to read outside of array");
      exit(EXIT_FAILURE);
   }

   *map_val += val;
   return *map_val;
}
   
static void show_direction(int direction, int *grid, int maxlen){
   static int presents;
   static int houses;
   static int step = 0;
   static int santax = 0;
   static int santay = 0;
   static int robox = 0;
   static int roboy = 0;
   static char *dirstring[] = { "START", "NORTH", "WEST", "EAST", "SOUTH" };

   if(direction < START || direction > SOUTH){
      logf(ERRERROR, "Invalid direction detected, '%d'", direction);
      return;
   }

   switch(direction){
      case NORTH:
         if(step % 2)
            santay--;
         else
            roboy--;
         break;
      case SOUTH:
         if(step % 2)
            santay++;
         else
            roboy++;
         break;
      case WEST:
         if(step % 2)
            santax--;
         else
            robox--;
         break;
      case EAST:
         if(step % 2)
            santax++;
         else
            robox++;
         break;
   }

   if(step % 2){
      presents = i2db_add(grid, maxlen, santax, santay, 1);
      if(presents == 1)
         houses++;

      logf(ERRDEBUG, "%8d: Santa go: %5s [%5d, %5d]/presents: %d total houses: %d", step++, dirstring[direction], santax, santay, presents, houses);
   }else{
      presents = i2db_add(grid, maxlen, robox, roboy, 1);
      if(presents == 1)
         houses++;

      logf(ERRDEBUG, "%8d:  Robo go: %5s [%5d, %5d]/presents: %d total houses: %d", step++, dirstring[direction], robox, roboy, presents, houses);
   }

}


int scan_instructions(FILE *infile, void dir_execute(int, int *, int), int *grid, int maxlen){
   int instruction_step = 0;
   char instruction;

   while(fread(&instruction, 1, 1, infile)){
      instruction_step++;

      switch (instruction){
         case '^':             // NORTH
            dir_execute(NORTH, grid, maxlen);
            break;
         case '<':             // WEST
            dir_execute(WEST, grid, maxlen);
            break;
         case '>':             // EAST
            dir_execute(EAST, grid, maxlen);
            break;
         case 'v':             // SOUTH
         case 'V':
            dir_execute(SOUTH, grid, maxlen);
            break;
         case '\n':
         case EOF:
            break;
         default:
            logf(ERRWARN, "bad instruction in inputfile, ignoring '%c'(%d) at step %d", instruction>31?instruction:' ', instruction, instruction_step);
      }
   }
   return 0;
}


static int logf(int level, char *fmt, ...){
   int retval;
   FILE *logoutfile = stderr;
   char *errlevelmsg[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

   va_list args;
   va_start(args, fmt);
   retval = fprintf(logoutfile, "%s: ", errlevelmsg[level]) +
            vfprintf(logoutfile, fmt, args) +
            fprintf(logoutfile, "\n");
   va_end(args);

   return retval;
}

static void usage(char *programName){
   printf("%s [instruction_file]\n", programName);
}
