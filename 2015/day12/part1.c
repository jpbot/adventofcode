#include "../common/advent.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define DEFAULTINPUTFILE "input_day12.in"

unsigned int
strFsplit (char *str, char **list, unsigned int list_size,
           const char *delim, unsigned int delim_size,
           const char quotechar);


int main(int argc, char** argv){
   int infile;
   FILE *inputfile;
   struct stat fdstat;
   char *buffer = 0;
   char **list = 0;
   int list_cnt;
   size_t read_bytes;
   char delims[] = { '[', ']', '{', '}', ',', ' ', ':' };
   unsigned int delims_sz = 7;
   long int sum = 0;

   loggerf(ERRINFO, "Input File: %s", DEFAULTINPUTFILE);

   stat(DEFAULTINPUTFILE, &fdstat);

   inputfile = fopen(DEFAULTINPUTFILE, "r");

   loggerf(ERRINFO, "Input file length: %d", fdstat.st_size);

   buffer = malloc(fdstat.st_size + 1);
   list = malloc(sizeof(char*) * fdstat.st_size / 4);

   if(!buffer){
      loggerf(ERRFATAL, "COULD NOT ALLOCATE MEMORY FOR: buffer");
      exit(EXIT_FAILURE);
   }
   if(!list){
      loggerf(ERRFATAL, "COULD NOT ALLOCATE MEMORY FOR: list");
      exit(EXIT_FAILURE);
   }

   buffer[fdstat.st_size] = 0;

   read_bytes = fread(buffer, fdstat.st_size, 1, inputfile);
   if(!read_bytes){
      loggerf(ERRFATAL, "Error reading file: read 0 bytes");
      exit(EXIT_FAILURE);
   }

   loggerf(ERRINFO, "Input file read, buffer length: %ul", strlen(buffer));

   list_cnt = strFsplit(buffer, list, fdstat.st_size / 4, delims, delims_sz, '"');

   for(int i = 0; i < list_cnt; i++){
      sum += atoi(list[i]);
//      printf("  %5d: [%9ld] %s\n", i, sum, list[i]);
   }
      printf("SUM: %ld\n", sum);
}



/**
 * strFsplit - Split a string
 *
 * strFsplit() splits the string @str into smaller strings, writing
 * the start of each sub-string into @list, up to a total of
 * @list_size elements.
 *
 * The string is split based on the @delim character, which specifies
 * a deliminter. Quote encoding is supported, and if desired, a quote
 * character should be specified as @quotechar.
 *
 * The remainder of the @str is placed into the last entry of @list,
 * even if the remainder contains more delimiter characters.
 *
 * @str must reference a NULL terminated string. @list must reference
 * valid storage.
 *
 * Availability: >= mk5 mod0.
 */
unsigned int
strFsplit (char *str, char **list, unsigned int list_size,
           const char *delim, const unsigned int delim_size,
           const char quotechar)
{
  register char *p, *sp;
  register unsigned int listc = 0;
  register short inquote = 0;
  register unsigned int i;
  assert (str != NULL);
  assert (list != NULL);
  assert (list_size > 0);

  list_size--;

  if (quotechar == 0)
    inquote = 3;

  for (sp = p = str; *p != 0; p++)
    {
      if (inquote == 1)
        {
          if (*p == quotechar)
            {
              inquote = 0;
            }
          continue;
        }
      if (inquote == 0)
        if (*p == quotechar)
          {
            inquote = 1;
            continue;
          }
      for(i = 0; i < delim_size; i++){
        if (*p == delim[i])
          {
            list[listc] = sp;
            if (listc == list_size)
              {
                return listc + 1;
              }
            *p = '\0';
            listc++;
            sp = (p + 1);
            break;
          }
      }
    }

  list[listc] = sp;
  return listc + 1;
}

