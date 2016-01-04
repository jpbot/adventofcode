// DAY 23
//
// HLF   1110 0010 0000 000x  divide register by 2. x=0 reg a. x=1 reg b.
// TPL   0111 0011 0000 000x  multiply register by 3. x=0 reg a. x=1 reg b. 
// INC   0001 0001 0000 000x  increment register by 1. x=0 reg a. x=1 reg b.
// JMP   1000 x000 yyyy yyyy  jump x=0 forward/x=1 backward yyyy yyyy positions
// JIE   1000 xz11 yyyy yyyy  if reg is even, z=0 reg a. z=1 reg b.
//                            jump x=0 forward/x=1 backward yyyy yyyy positions
// JIO   1000 xz01 yyyy yyyy  if reg == 1, z=0 reg a. z=1 reg b.
//                            jump x=0 forward/x=1 backward yyyy yyyy positions

#define IN_HLF 0b11100010
#define IN_TPL 0b01110011
#define IN_INC 0b00010001
#define IN_JMP 0b10000000
#define IN_JIE 0b10000010
#define IN_JIO 0b10000011

#define REG_A 1
#define REG_B 2
#define SIGN_POS 1
#define SIGN_NEG -1

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "../common/advent.h"

#define DEFAULTINPUTFILE "input_day23.in"
#define MAXLINELEN 40

typedef struct{
   uint16_t  op;
   int8_t  sign1;
   int8_t  sign2;
   uint16_t arg1;
   uint16_t arg2;
} instruction_t;

static void usage(char *programName);
static char * instruction_name(uint16_t op);

static int str1ch(char *d, size_t maxlen, const char search, const char replace);
static int op_token(char *d, char **op, char **arg1, char **arg2);
static int arg_sign(char **arg);

int main(int argc, char **argv){
   char *inputfile = 0;
   FILE *infile;
   char buffer[MAXLINELEN + 1];
   char *op = 0;
   char *arg1 = 0;
   char *arg2 = 0;
   int list_sz = 0;
   int sign1, sign2;
   instruction_t *instructions = 0;
   instruction_t *inst = 0;
   int instlist_sz = 0;
   int current_inst = 0;
   int reg_a = 0;
   int reg_b = 0;
   int step = 0;

   //PART B
  reg_a = 1;

   uint16_t instruction;

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
            loggerf(ERRDEBUG, "[%3d]:%s|(%d)%s|(%d)%s:", list_sz, op, sign1, arg1, sign2, arg2);
            instructions = realloc(instructions, sizeof(instruction_t) * (instlist_sz + 2));
            inst = instructions + instlist_sz;
            instlist_sz++;

            loggerf(ERRDEBUG, "%d", inst);
            inst->op = instruction;
            inst->arg1 = arg1!=0?atoi(arg1):0;
            inst->arg2 = arg2!=0?atoi(arg2):0;
            inst->sign1 = sign1;
            inst->sign2 = sign2;
            if(instruction != IN_JMP){
               switch(arg1[0]){
                  case 'a':
                     inst->arg1 = REG_A;
                     break;
                  case 'b':
                     inst->arg1 = REG_B;
                     break;
                }
            }
         }
      }
   }
   fclose(infile);

   loggerf(ERRDEBUG, "BEGIN RUN");
   loggerf(ERRINFO, "[%04d] INSTRUCTION %4d/%4d :: a = %d, b = %d", step++, current_inst, instlist_sz, reg_a, reg_b);
   while(current_inst < instlist_sz){
      inst = instructions + current_inst++;

loggerf(ERRDEBUG, "arg1 = %d", inst->arg1);
loggerf(ERRDEBUG, "arg2 = %d", inst->arg2);
loggerf(ERRDEBUG, "sign1 = %d", inst->sign1);
loggerf(ERRDEBUG, "sign2 = %d", inst->sign2);

      switch(inst->op){
         case IN_HLF:
            switch(inst->arg1){
               case REG_A:
                  reg_a /= 2;
                  break;
               case REG_B:
                  reg_b /= 2;
                  break;
            }
            break;
         case IN_TPL:
            switch(inst->arg1){
               case REG_A:
                  reg_a *= 3;
                  break;
               case REG_B:
                  reg_b *= 3;
                  break;
            }
            break;
         case IN_INC:
            switch(inst->arg1){
               case REG_A:
                  reg_a++;
                  break;
               case REG_B:
                  reg_b++;
                  break;
            }
            break;
         case IN_JMP:
            if(inst->sign1 == SIGN_POS){
               current_inst += (inst->arg1 - 1);
            } else {
               current_inst -= (inst->arg1 + 1);
            }
            break;
         case IN_JIE:
            {
               int temp;
               switch(inst->arg1){
                  case REG_A:
                     temp = reg_a;
                     break;
                  case REG_B:
                     temp = reg_b;
                     break;
               }
               if(temp % 2 == 0){
                  if(inst->sign2 == SIGN_POS){
                     current_inst += (inst->arg2 - 1);
                  } else {
                     current_inst -= (inst->arg2 + 1);
                  }
              }
            }
            break;
         case IN_JIO:
            {
               int temp;
               switch(inst->arg1){
                  case REG_A:
                     temp = reg_a;
                     break;
                  case REG_B:
                     temp = reg_b;
                     break;
               }
               if(temp == 1){
                  if(inst->sign2 == SIGN_POS){
                     current_inst += (inst->arg2 - 1);
                  } else {
                     current_inst -= (inst->arg2 + 1);
                  }
              }
            }
            break;
      }

      loggerf(ERRINFO, "[%04d] INSTRUCTION [%s] %4d/%4d :: a = %d, b = %d", step++, instruction_name(inst->op), current_inst, instlist_sz, reg_a, reg_b);
   }

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

static char * instruction_name(uint16_t op){
   static char *op_names[] = {
      "HLF",
      "TPL",
      "INC",
      "JMP",
      "JIE",
      "JIO"};

   switch(op){
      case IN_HLF:
         return op_names[0];
      case IN_TPL:
         return op_names[1];
      case IN_INC:
         return op_names[2];
      case IN_JMP:
         return op_names[3];
      case IN_JIE:
         return op_names[4];
      case IN_JIO:
         return op_names[5];
   }
  return 0;
}

static void usage(char *programName){
   printf("%s [input_file]\n", programName);
}
