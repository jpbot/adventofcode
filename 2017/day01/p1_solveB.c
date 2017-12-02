// ================================================================
// Advent of Code 2017
// http://adventofcode.com
//
// Solution in C'
// Day 1b
// ================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERBOSE(f_, ...)
// #define VERBOSE(...) printf( __VA_ARGS__)

void err_report(const char *msg, int errlevel){
   printf("%d: %s\n", errlevel, msg);
   exit(errlevel);
}

int main(int argc, char **argv){
   char defaultFile[] = "p1_input.txt";
   const int block_sz = 512; //1024;
   char *inputFile = defaultFile;;
   FILE *in = NULL;
   char *buffer;
   unsigned long buffer_sz = block_sz;
   unsigned long comp;
   size_t bytes = 0;
   size_t readBytes = block_sz;

   // deterimne the input source
   if(argc > 1){
      if(!strcmp(argv[1], "-")){
         in = stdin;
         VERBOSE("Reading from STDIN\n");
      } else {
         inputFile = argv[1];
         VERBOSE("Reading from %s\n", inputFile);
      }
   }

   // open the file if needed
   if(in == NULL) {
      in = fopen(inputFile, "r");
      VERBOSE("Opened file %s\n", inputFile);
   }
   if(in == NULL) {
      printf("1: Can't open file '%s'.\n", inputFile);
      return 1;
   }
   
   // read the input into a buffer.
   buffer = malloc(buffer_sz);
   if(buffer == NULL) err_report("Memory error allocating buffer.", 2);
   VERBOSE("Allocated %lu byes for buffer\n", buffer_sz);

   while(readBytes == block_sz){
      readBytes = fread(buffer + bytes, 1, block_sz, in);
      VERBOSE("Read %zu bytes.", readBytes);
      bytes += readBytes;

      if(readBytes == block_sz){
         VERBOSE(" REALLOC buffer %lu->%lu", buffer_sz, buffer_sz + block_sz);
         if((buffer = realloc(buffer, buffer_sz + block_sz)) == NULL){
            err_report("Memory error growing buffer.", 3);
         }
         buffer_sz += block_sz;
         VERBOSE(": SUCCESS");
      }
      VERBOSE("\n");
   } while(readBytes == block_sz);


   // print read status
   printf("Data read complete.\n");
   printf("  buffer size: %zu\n  allocation block size: %d\n  bytes read: %zu\n", buffer_sz, block_sz, bytes);

   // convert ascii to dec value, test for EOF or other cruft.
   size_t accepted = 0; //storage for output array location

   for(size_t i = 0; i < bytes; i++){
      if(buffer[i] >= '0' && buffer[i] <= '9'){ 
         buffer[accepted++] = buffer[i] - '0';
      }
   }
 
   printf("Accepted Bytes: %zu\n\n", accepted);

   // process data
   size_t offset;
   int accumulator = 0;

   offset = accepted / 2;

   for(size_t i = 0; i < accepted; i++){
      VERBOSE("buffer[%zu] == buffer[(%zu+%zu) %% %zu] ::: %d == %d ::: ",i, i, offset, accepted, buffer[i], buffer[(i+offset) % accepted]);
      if(buffer[i] == buffer[(i+offset) % accepted]){
         accumulator += buffer[i];
         VERBOSE("TRUE    :: accumulator += buffer[%zu] %c (%d)\n", i, buffer[i], accumulator);
      } else {
         VERBOSE("FALSE\n");
      }
   }

   VERBOSE("\n");
   printf("ACCUMULATOR: %d\n", accumulator);

   return 0;
}
