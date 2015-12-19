// DAY 10  -  FAST
// preallocates enough memory in the buffers
// minimizes math by working with chars as a unsigned ints instead of ASCII

#include "../common/advent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void looksay(const char *d, char *o, size_t dlen);

int main(int argc, char **argv){
   size_t bufferlen = 6 * 1024 * 1024;
   char *input_buffer, *output_buffer, *temp;
   int input_len = strlen(PUZZLEINPUTDAY10);
   int i = 0;

   input_buffer = malloc(bufferlen);
   output_buffer = malloc(bufferlen);

   loggerf(ERRDEBUG, "input: %s", PUZZLEINPUTDAY10);

   strcpy(input_buffer, PUZZLEINPUTDAY10);
   for(int i = 0; i < input_len; i++){
      input_buffer[i] -= 48;
   }


   for(; i < 50; i++){
      looksay(input_buffer, output_buffer, bufferlen);
      if(i == 40) loggerf(ERRINFO, "LOOKSAY%02d: [%d]", i+1, strlen(input_buffer));

      temp = input_buffer;
      input_buffer = output_buffer;
      output_buffer = temp;
   }
   loggerf(ERRINFO, "LOOKSAY%02d: [%d]", i+1, strlen(input_buffer));

   free(input_buffer);
   free(output_buffer);

   return EXIT_SUCCESS;
}

void looksay(const char *d, char *o, size_t olen){
   char lastdigit = *d++;
   int digitcount = 1;

   while(*d != 0){
      if(*d == lastdigit){
         digitcount++;
      } else {
         *o++ = digitcount;
         *o++ = lastdigit;
         lastdigit = *d;
         digitcount = 1;
      }
      d++;
   }

   *o++ = digitcount;
   *o++ = lastdigit;
   *o = 0;
}
