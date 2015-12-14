#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define ERRDEBUG 0
#define ERRINFO 1
#define ERRWARN 2
#define ERRERROR 3
#define ERRFATAL 4

#define DEFAULTINPUTFILE "input_day1.in"
static int logf(int level, char *fmt, ...);
static void usage(char *programName);
int scan_instructions(FILE *inputfile, int searchfloor);

int main(int argc, char **argv){
   int searchfloor = 0;
   int instruction_step = 0;
   char *inputfile = 0;
   char instruction = 0;
   FILE *infile;

   if(argc < 2){
      logf(ERRFATAL, "must specify floor to search for.");
      usage(argv[0]);
      return EXIT_FAILURE;
   }

   if(argc < 3){   //set default file
      inputfile = malloc(strlen(DEFAULTINPUTFILE) + 1);
      if(!inputfile){
         logf(ERRFATAL, "couldn't allocate memory for input file name.");
         return EXIT_FAILURE;
      }
      strcpy(inputfile, DEFAULTINPUTFILE);
   } else {
      inputfile = argv[2];
   }
   logf(ERRINFO, "Input file: %s", inputfile);

   searchfloor = atoi(argv[1]);
   logf(ERRINFO, "searching for instruction step for first entry to floor: %d", searchfloor);

   infile = fopen(inputfile, "r");
   if(!infile){
      logf(ERRFATAL, "could not open file %s for input. Cannot continue.", inputfile);
      return EXIT_FAILURE;
   }

   instruction_step = scan_instructions(infile, searchfloor);

   if(instruction_step == -1){
      logf(ERRINFO, "%d floor not found in instruction file %s.", searchfloor, inputfile);
   } else {
      logf(ERRINFO, "Found floor %d at instruction %d.", searchfloor, instruction_step);
   }

   return EXIT_SUCCESS;
}

int scan_instructions(FILE *infile, int searchfloor){
   int currentfloor = 0;
   int instruction_step = 0;
   char instruction;

   while(fread(&instruction, 1, 1, infile)){
      if(currentfloor == searchfloor) return instruction_step;
      instruction_step++;
      switch (instruction){
         case '(':
            currentfloor++;
            break;
         case ')':
            currentfloor--;
            break;
         default:
            logf(ERRWARN, "bad instruction in inputfile, ignoring '%c' at step %d", instruction>31?instruction:' ', instruction_step);
      }
   }
   if(currentfloor == searchfloor) return instruction_step;
   return -1;
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
   printf("%s <floor_to_search_for> [instruction_file]\n", programName);
}
