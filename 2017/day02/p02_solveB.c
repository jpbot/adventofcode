// ================================================================
// Advent of Code 2017
// http://adventofcode.com
//
// Solution in C
// Day 02b
// ================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define VERBOSE(f_, ...)
#define VERBOSE(...) printf( __VA_ARGS__)

int main(int argc, char **argv){
   char defaultFile[] = "p02_input.txt";
   char *inputFile = defaultFile;;
   FILE *in = NULL;

   // check for file on command line
   if(argc > 1){
      if(!strcmp(argv[1], "-")){
         // STDIN, woohoo
         in = stdin;
      } else {
         inputFile = argv[1];
      }
   }

   // if we aren't using STDIN for the file source we need to open a file
   if(in == NULL) in = fopen(inputFile, "r");
   if(in == NULL){
      printf("Can't open file '%s'.\n", inputFile);
      return 1;
   }
   

   // SOLUTION starts here

   size_t buffer_sz = 2000;
   char *val;
   char *buffer = malloc(buffer_sz);
   int lineRead;
   int v1, v2, intCount;
   int intList[buffer_sz];
   int lines = 0;
   int bytes = 0;
   int accepted = 0;
   int acceptedLines = 0;
   int checksum = 0;

   while(fgets(buffer, buffer_sz, in)){
      // READ a line
      lineRead = strlen(buffer);
      bytes += lineRead;

      VERBOSE("LINEREAD: %5d: %3d bytes (%7d): ", (lines + 1), lineRead, bytes);

      // check for empty last line (EOF)
      if(lineRead == 0) break;

      lines++;

      //check for newline
      if(buffer[lineRead-1] == '\n'){
         buffer[--lineRead] = 0;
      } else {
         printf("NO NEWLINE, ignoring line.");
         while(buffer[lineRead-1] != '\n' && fgets(buffer, buffer_sz, in));
 
         continue;
      }

      acceptedLines++;
      accepted += lineRead;

      VERBOSE("%s\n", buffer);

      // add values to int array
      val = strtok(buffer, "\t ");
      intCount = 0;
      while(val != NULL){
         intList[intCount++] = atoi(val);
         val = strtok(NULL, "\t ");
      }

      // check for two values that can divide
      for(v1 = 0; v1 < intCount - 1; v1++){
         if(intList[v1] == 0) continue;
 
         for(v2 = v1 + 1; v2 < intCount; v2++){
            if(intList[v2] == 0) continue;

	    if(intList[v1] % intList[v2] == 0){
	       checksum += intList[v1] / intList[v2];
               v1 = intCount;
	       break;
	    }
            if(intList[v2] % intList[v1] == 0){
               checksum += intList[v2] / intList[v1];
               v1 = intCount;
               break;
            }
         }
      }

   }

   printf("lines processed: %d\nCHEECKSUM: %d\n", lines, checksum);

   fclose(in);
   return 0;
}
