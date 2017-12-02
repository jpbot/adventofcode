// ================================================================
// Advent of Code 2017
// http://adventofcode.com
//
// Solution in C
// Day 1a
// ================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
   char defaultFile[] = "p1_input.txt";
   char *inputFile = defaultFile;;
   FILE *in = NULL;

   if(argc > 1){
      if(!strcmp(argv[1], "-")){
         in = stdin;
      } else {
         inputFile = argv[1];
      }
   }

   if(in == NULL) in = fopen(inputFile, "r");
   if(in == NULL){
      printf("Can't open file '%s'.\n", inputFile);
      return 1;
   }
   
   int accumulator = 0;
   char first = 11;
   char last = 0;
   char c;
   int bytes = 0;
   int accepted = 0;
   int summed = 0;

   while((c=fgetc(in)) != EOF){
      bytes++;
      if(c >= '0' && c <= '9'){
         accepted++;
         c -= '0';

         if(first == 11) first = c;
         if(c == last){
            summed++;
            accumulator += c;
         }

         last = c;
      }
   }

   if(first == last){
      summed++;
      accumulator += last;
   }

   printf("READ: %d\nACCEPTED: %d\nSUMMED: %d\tACCUMULATOR: %d\n", bytes, accepted, summed, accumulator);
   return 0;
}
