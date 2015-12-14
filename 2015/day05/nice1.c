#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define ERRDEBUG 0
#define ERRINFO 1
#define ERRWARN 2
#define ERRERROR 3
#define ERRFATAL 4

#define DEFAULTINPUTFILE "input_day05.in"
#define MAXLINELEN 80

static int logf(int level, char *fmt, ...);
static void usage(char *programName);

int scan_file(FILE *infile, int calc_func(int, int, int));
static int test_nice(const char *d);
static int str1ch(char *d, size_t maxlen, const char search, const char replace);

int main(int argc, char **argv){
   char *inputfile = 0;
   FILE *infile;
   char buffer[MAXLINELEN + 1];
   int nice_str = 0;

   char test1[] = "ugknbfddgicrmopn";
   char test2[] = "aaa";
   char test3[] = "jchzalrnumimnmhp";
   char test4[] = "haegwjzuvuyypxyu";
   char test5[] = "dvszwmarrgswjxmb";

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

   logf(ERRDEBUG, "TEST: %20s: %s", test1, test_nice(test1)?"NICE":"NAUGHTY");
   logf(ERRDEBUG, "TEST: %20s: %s", test2, test_nice(test2)?"NICE":"NAUGHTY");
   logf(ERRDEBUG, "TEST: %20s: %s", test3, test_nice(test3)?"NICE":"NAUGHTY");
   logf(ERRDEBUG, "TEST: %20s: %s", test4, test_nice(test4)?"NICE":"NAUGHTY");
   logf(ERRDEBUG, "TEST: %20s: %s", test5, test_nice(test5)?"NICE":"NAUGHTY");

   while(fgets(buffer, MAXLINELEN, infile)) {
      if(str1ch(buffer, MAXLINELEN, '\n', 0) > 0){;
         if(test_nice(buffer)){
            nice_str++;
            //logf(ERRINFO, "string: %20s: %s", buffer, test_nice(buffer)?"NICE":"NAUGHTY");
         }
      }
   }
   fclose(infile);

   logf(ERRINFO, "%d nice strings in input file: %s", nice_str, inputfile);

   return EXIT_SUCCESS;
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
