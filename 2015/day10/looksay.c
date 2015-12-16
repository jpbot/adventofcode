#include "../common/advent.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int isdigit(const char c);
int looksay(const char *d, char *o, size_t dlen);
void swap(char **x1, char **x2);

int main(int argc, char **argv){
   size_t bufferlen;
   char *input_buffer;
   char *output_buffer;
   int len;

   bufferlen = 24;

   input_buffer = malloc(bufferlen);
   output_buffer = malloc(bufferlen);

   loggerf(ERRDEBUG, "input: %s", PUZZLEINPUTDAY10);

   strcpy(input_buffer, PUZZLEINPUTDAY10);
   for(int i = 0; i < 50;){
      len = looksay(input_buffer, output_buffer, bufferlen);

      if(len < 0) {     // exceeded output buffer, rerun.
         if(bufferlen < MAX_BUFFER_INCREMENT)
            bufferlen *= 2;
         else
            bufferlen += MAX_BUFFER_INCREMENT;

         char *temp = realloc(input_buffer, bufferlen);
         input_buffer = temp;
         free(output_buffer);
         output_buffer = malloc(bufferlen);
      } else {
        i++;

         loggerf(ERRINFO, "LOOKSAY%02d: [%d]", i, len);
         // loggerf(ERRINFO, "LOOKSAY%02d (%s): %s [%d]", i, input_buffer, output_buffer, len);

         swap(&input_buffer, &output_buffer);
      }
   }

   free(input_buffer);
   free(output_buffer);

   return EXIT_SUCCESS;
}

int looksay(const char *d, char *o, size_t olen){
   char lastdigit = 0;
   int digitcount;
   int outputphraselen;
   int outputlen = 0;

   while(*d != 0){
      if(!isdigit(*d)) {
         loggerf(ERRFATAL, "INVALID INPUT, '%c' is not a digit.", *d);
         exit(EXIT_FAILURE);
      }

      if(*d == lastdigit){
         digitcount++;
      } else {
         if(lastdigit){
            outputphraselen = snprintf(o, olen, "%d%c", digitcount, lastdigit);
            outputlen += outputphraselen;
            if(outputphraselen < olen){
               olen -= (outputphraselen);
               o += outputphraselen;
               //loggerf(ERRDEBUG, "olen=%d, outputphraselen=%d, outputlen=%d", olen, outputphraselen, outputlen);
            } else {
               loggerf(ERRDEBUG, "buffer to small, increase buffer to looksay.");
               return -1;
            }
         }
         lastdigit = *d;
         digitcount = 1;
      }

      d++;
   }

   outputphraselen = snprintf(o, olen, "%d%c", digitcount, lastdigit);
   outputlen += outputphraselen;
   if(outputphraselen < olen){
      olen -= (outputphraselen + 1);
      o += outputphraselen;
   } else {
      loggerf(ERRDEBUG, "buffer to small, increase buffer to looksay.");
      return -1;
   } 

   return outputlen;
}

void swap(char **x1, char **x2){
   char *temp = *x1;
   *x1 = *x2;
   *x2 = temp;
}

int isdigit(const char c){
   return c>='0' && c<='9';
}
