#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define ERRDEBUG 0
#define ERRINFO 1
#define ERRWARN 2
#define ERRERROR 3
#define ERRFATAL 4

#define DEFAULTINPUTFILE "input_day2.in"
#define MAXLINELEN 80

static int logf(int level, char *fmt, ...);
static void usage(char *programName);

int scan_file(FILE *infile, int calc_func(int, int, int));
int wrap_area(int l, int w, int h);
int ribbon_pack(int x, int y, int z);
int smallest_perimeter(int x, int y, int z);
int volume(int x, int y, int z);
int parse_volume_str(char *buffer, int buflen, int *x, int *y, int *z);

int main(int argc, char **argv){
   char *inputfile = 0;
   FILE *infile;
   int totalribbon;

   if(argc < 2){   //set default file
      inputfile = malloc(strlen(DEFAULTINPUTFILE) + 1);
      if(!inputfile){
         logf(ERRFATAL, "couldn't allocate memory for input file name.");
         return EXIT_FAILURE;
      }
      strcpy(inputfile, DEFAULTINPUTFILE);
   } else {
      inputfile = argv[1];
   }
   logf(ERRINFO, "Input file: %s", inputfile);


   infile = fopen(inputfile, "r");
   if(!infile){
      logf(ERRFATAL, "could not open file %s for input. Cannot continue.", inputfile);
      return EXIT_FAILURE;
   }
   logf(ERRDEBUG, "TEST: 2x4x6: %d", wrap_area(2,4,6));
   logf(ERRDEBUG, "TEST: 2x6x4: %d", wrap_area(2,6,4));
   logf(ERRDEBUG, "TEST: 4x2x6: %d", wrap_area(4,2,6));
   logf(ERRDEBUG, "TEST: 4x6x2: %d", wrap_area(4,6,2));
   logf(ERRDEBUG, "TEST: 6x2x4: %d", wrap_area(6,2,4));
   logf(ERRDEBUG, "TEST: 6x4x2: %d", wrap_area(6,4,2));

   totalribbon = scan_file(infile, &ribbon_pack);
   logf(ERRINFO, "Please order %d feet of ribbon", totalribbon);

   fclose(infile);

   return EXIT_SUCCESS;
}

int scan_file(FILE *infile, int calc_func(int, int, int)){
   char buffer[MAXLINELEN + 1];
   char *bufpos = buffer;
   char ch = 0;
   int x, y, z;
   int retval = 0;

   ch = (char) fgetc(infile);
   while(ch != EOF){
      if(ch == '\n'){
         *bufpos = 0;
         parse_volume_str(buffer, bufpos - buffer, &x, &y, &z);
         retval += calc_func(x, y, z);
         bufpos = buffer;
      }else{
         // logf(ERRDEBUG, "READ: '%c'", ch);
         *bufpos++ = ch;
      }

      if(bufpos-buffer > MAXLINELEN){
         logf(ERRFATAL, "Line length too long, fatal error.");
         exit(EXIT_FAILURE);
      }

      ch = (char) fgetc(infile);
   }

   return retval;
}

int ribbon_pack(int x, int y, int z){
   return volume(x, y, z) + smallest_perimeter(x, y, z);
}

int volume(int x, int y, int z){
   return x * y * z;
}

int smallest_perimeter(int x, int y, int z){
   int dim1 = x;
   int dim2 = y;

   if(dim1 > dim2){  // check that x is not greater than z
      if(dim1 > z) dim1 = z;
   } else {          // check that y is not greater than z
      if(dim2 > z) dim2 = z;
   }

   return (2 * dim1) + (2 * dim2);
}

int wrap_area(int l, int w, int h){
   int extra_dim1 = l;
   int extra_dim2 = w;
   int area = 0;

   if(extra_dim1 > extra_dim2){  //check that l is not greater than h
      if(extra_dim1 > h) extra_dim1 = h;
   }else{  // check that w is not greater than h
      if(extra_dim2 > h) extra_dim2 = h;
   }

   area = 2 * (l * w) +
          2 * (l * h) +
          2 * (w * h) +
          (extra_dim1 * extra_dim2);

   return area;
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
   printf("%s [input_file]\n", programName);
}

int parse_volume_str(char *buffer, int buflen, int *x, int *y, int *z){
   char *buffermax = buffer + buflen;
   char *xstr = buffer;
   char *ystr = 0;
   char *zstr = 0;

   logf(ERRDEBUG, "PARSEVOLSTR:    buffer = '%s'", buffer);
   logf(ERRDEBUG, "PARSEVOLSTR: buffermax = '%s'", buffermax);
   logf(ERRDEBUG, "PARSEVOLSTR:    buflen = %d", buflen);

   for(; buffer < buffermax; buffer++){
      if(*buffer == 'x') break;
   }
   *buffer = 0;

   ystr = ++buffer;
   for(; buffer < buffermax; buffer++){
      if(*buffer == 'x') break;
   }
   *buffer = 0;

   zstr = ++buffer;
   logf(ERRDEBUG, "PARSEVOLSTR:    zstr = '%s'", zstr);
   for(; buffer < buffermax; buffer++){
      if(*buffer == 'x') break;
   }
   *buffer = 0;
   logf(ERRDEBUG, "PARSEVOLSTR:    zstr = '%s'", zstr);

   *x = atoi(xstr);
   *y = atoi(ystr);
   *z = atoi(zstr);

   return 0;
}

