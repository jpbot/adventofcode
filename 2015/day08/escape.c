#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define ERRDEBUG 0
#define ERRINFO 1
#define ERRWARN 2
#define ERRERROR 3
#define ERRFATAL 4

#define DEFAULTINPUTFILE "input_day08.in"
#define MAXLINELEN 80

static int logf(int level, char *fmt, ...);
static void usage(char *programName);

static int str1ch(char *d, size_t maxlen, const char search, const char replace);
static int strvallen(const char *d, int dlen);

int main(int argc, char **argv){
   char *inputfile = 0;
   FILE *infile;
   char buffer[MAXLINELEN + 1];
   int list_sz = 0;

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

   while(fgets(buffer, MAXLINELEN, infile)) {
      if(str1ch(buffer, MAXLINELEN, '\n', 0) > 0){
         list_sz += strlen(buffer) - strvallen(buffer, strlen(buffer)) + 2;
         // logf(ERRINFO, "string: %50s: len: %2d vallen: %2d", buffer, strlen(buffer), strvallen(buffer, strlen(buffer)));
      }
   }
   fclose(infile);

   logf(ERRINFO, "Size of overhead: %d", list_sz);

   return EXIT_SUCCESS;
}

int strvallen(const char *d, int dlen){
   int str_sz = 0;

   while(--dlen >= 0){
      if(*d == '\\'){
         --dlen;
         d++;
         if(*d == 'x'){
            d += 2;
            dlen -= 2;
         } else if(*d != '\\' && *d != '\"'){
            return -1;     // invalid escape sequience
         }
      }     
      d++;
      str_sz++;
   }

   return str_sz;
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

static int test_nice(const char *d){
   static int i;
   int nice = 0;
   int vowel_ct = 0;
   size_t len = strlen(d);
   char last_char;

   for(i = 0; i < len; i++){
      if(d[i] == 'a') vowel_ct++;
      if(d[i] == 'e') vowel_ct++;
      if(d[i] == 'i') vowel_ct++;
      if(d[i] == 'o') vowel_ct++;
      if(d[i] == 'u') vowel_ct++;

      if(i>0){
         if(d[i - 1] == d[i]) nice++;
         if(d[i - 1] == 'a' && d[i] == 'b') return 0;
         if(d[i - 1] == 'c' && d[i] == 'd') return 0;
         if(d[i - 1] == 'p' && d[i] == 'q') return 0;
         if(d[i - 1] == 'x' && d[i] == 'y') return 0;
      }
   }

   if(vowel_ct > 2 && nice) return 1;
   return 0;
}
