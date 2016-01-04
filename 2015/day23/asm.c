// DAY 23
//
// HLF   1110 0010 0000 000x  divide register by 2. x=0 reg a. x=1 reg b.
// TPL   0111 0011 0000 000x  multiply register by 3. x=0 reg a. x=1 reg b. 
// INC   0001 0001 0000 000x  increment register by 1. x=0 reg a. x=1 reg b.
// JMP   1000 x000 yyyy yyyy  jump x=0 forward/x=1 backward yyyy yyyy positions
// JIE   1000 xz11 yyyy yyyy  if reg is even, z=0 reg a. z=1 reg b.
//                            jump x=0 forward/x=1 backward yyyy yyyy positions
// JIO   1000 xz01 yyyy yyyy  if reg is odd, z=0 reg a. z=1 reg b.
//                            jump x=0 forward/x=1 backward yyyy yyyy positions

#define IN_HLF 0b11100010
#define IN_TPL 0b01110011
#define IN_INC 0b00010001
#define IN_JMP 0b10000000
#define IN_JIE 0b10000010
#define IN_JIO 0b10000011

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "../common/advent.h"

#define DEFAULTINPUTFILE "input_day23.in"
#define OUTPUTFILE "a.out"
#define MAXLINELEN 80

static void usage(char *programName);

static int str1ch(char *d, size_t maxlen, const char search, const char replace);
static int op_token(char *d, char **op, char **arg1, char **arg2);
static int arg_sign(char **arg);

int main(int argc, char **argv){
   char *inputfile = 0;
   char *outputfile = 0;
   FILE *infile;
   FILE *outfile;
   char buffer[MAXLINELEN + 1];
   char *op = 0;
   char *arg1 = 0;
   char *arg2 = 0;
   int list_sz = 0;
   int sign1, sign2;

   uint16_t instruction;
   unsigned int instructions = 0;

   if(argc < 2){   //set default file
      inputfile = malloc(strlen(DEFAULTINPUTFILE) + 1);
      if(!inputfile){
         loggerf(ERRFATAL, "couldn't allocate memory for input file name.");
         return EXIT_FAILURE;
      }
      strcpy(inputfile, DEFAULTINPUTFILE);
   } else {
      inputfile = argv[1];
   }
   loggerf(ERRINFO, "Input file: %s", inputfile);

   outputfile = malloc(strlen(OUTPUTFILE) + 1);
   strcpy(outputfile, OUTPUTFILE);
   outfile = fopen(outputfile, "w");

   loggerf(ERRINFO, "Output file: %s", outputfile);

   infile = fopen(inputfile, "r");
   if(!infile){
      loggerf(ERRFATAL, "could not open file %s for input. Cannot continue.", inputfile);
      return EXIT_FAILURE;
   }

   while(fgets(buffer, MAXLINELEN, infile)) {
      if(str1ch(buffer, MAXLINELEN, '\n', 0) > 0){
         loggerf(ERRDEBUG, "[%08d] '%s'", list_sz, buffer);
         list_sz++;
         op_token(buffer, &op, &arg1, &arg2);
         sign1 = arg_sign(&arg1);
         sign2 = arg_sign(&arg2);
         instruction = 0xFFFF;
         if(strcmp("hlf", op) == 0) instruction = IN_HLF;
         if(strcmp("tpl", op) == 0) instruction = IN_TPL;
         if(strcmp("inc", op) == 0) instruction = IN_INC;
         if(strcmp("jmp", op) == 0) instruction = IN_JMP;
         if(strcmp("jie", op) == 0) instruction = IN_JIE;
         if(strcmp("jio", op) == 0) instruction = IN_JIO;
         if(instruction == 0xFFFF){
            loggerf(ERRWARN, "error parsing line '%s'", buffer);
         } else {
            // loggerf(ERRDEBUG, "[%3d]:%s|(%d)%s|(%d)%s:", list_sz, op, sign1, arg1, sign2, arg2);
         }
      }
   }
   fclose(outfile);
   fclose(infile);

   return EXIT_SUCCESS;
}

static int arg_sign(char **arg){
   if(!*arg)
      return 0;

   if(**arg == '-'){
     (*arg)++;
     return -1;
   }
   if(**arg == '+'){
      (*arg)++;
      return 1;
   }
   return 0;
}

// sloppy tokenizer is sloppy
// - poor bounds checking
// - multiple whitespace is not handled well
static int op_token(char *d, char **op, char **arg1, char **arg2){
   *op = 0;
   *arg1 = 0;
   *arg2 = 0;

   if(*d){
      *op = d;
      while(*d != ' ' && *d != 0)
         d++;
      if(*d == 0)
         return 1;
      *d = 0;
      d++;

      if(*d){
         *arg1 = d;
         while(*d != ',' && *d != 0)
            d++;
         if(*d == 0)
            return 1;
         *d = 0;
         d++;

         if(*d){
            if(*d == ' ') d++;
            *arg2 = d;
         }
         return 1;
      }
   }
   return 0;
}

static int str1ch(char *d, size_t maxlen, const char search, const char replace){
   static int i;
   for(i = 0; i < maxlen; i++){
      if(d[i] == search){
         d[i] = replace;
         return i;
      }
   }

   return -1;
}

static void usage(char *programName){
   printf("%s [input_file]\n", programName);
}
