#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define ERRDEBUG 0
#define ERRINFO 1
#define ERRWARN 2
#define ERRERROR 3
#define ERRFATAL 4

#define DEFAULTINPUTFILE "input_day06.in"
#define MAXLINELEN 80
#define MAXLIGHTS 1000*1000

static int logf(int level, char *fmt, ...);
static void usage(char *programName);

int scan_file(FILE *infile, int calc_func(int, int, int));
static int str1ch(char *d, size_t maxlen, const char search, const char replace);
size_t light_count(char *lights, size_t count);
void light_set(char *lights, char set, int x, int y, int max_x);
char light_get(char *lights, int x, int y, int max_x);
void light_toggle(char *lights, int x, int y, int max_x);
void light_set_range(char *lights, char set, int x1, int y1, int x2, int y2, int max_x);
void light_toggle_range(char *lights, int x1, int y1, int x2, int y2, int max_x);

int main(int argc, char **argv){
   char *inputfile = 0;
   FILE *infile;
   char buffer[MAXLINELEN + 1];
   char lights[MAXLIGHTS];

   memset(lights, 0, MAXLIGHTS * sizeof(char));

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
      if(str1ch(buffer, MAXLINELEN, '\n', 0) > 0){;
         logf(ERRDEBUG, "READ: %s", buffer);
      }
   }
   fclose(infile);

/*
   light_set(lights, 1, 0, 0, 1000);    logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_set(lights, 1, 1, 1, 1000);    logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_set(lights, 1, 0, 999, 1000);    logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_set(lights, 1, 999, 0, 1000);    logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_set(lights, 1, 999, 999, 1000);    logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
 */

/*
   light_set_range(lights, 1, 0, 0, 999, 999, 1000);  logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_set_range(lights, 0, 0, 0, 999, 999, 1000);  logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_set_range(lights, 1, 0, 0, 999, 0, 1000);  logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_set_range(lights, 1, 0, 0, 499, 500, 1000);  logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_set_range(lights, 0, 0, 0, 499, 500, 1000);  logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_set_range(lights, 0, 0, 0, 999, 999, 1000);  logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_toggle_range(lights, 499, 499, 500, 500, 1000);  logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
   light_toggle_range(lights, 499, 499, 500, 500, 1000);  logf(ERRDEBUG, "%lu LIGHTS", light_count(lights, MAXLIGHTS));
 */


   // TODO: Parse input string

   logf(ERRINFO, "%lu lights remain on following directions from input file: %s", light_count(lights, MAXLIGHTS), inputfile);

   return EXIT_SUCCESS;
}

void light_set_range(char *lights, char set, int x1, int y1, int x2, int y2, int max_x){
   for(int x = x1; x < x2 + 1; x++){
      for(int y = y1; y < y2 + 1; y++){
         light_set(lights, set, x, y, max_x);
      }
   }
}

void light_toggle_range(char *lights, int x1, int y1, int x2, int y2, int max_x){
   for(int x = x1; x < x2 + 1; x++){
      for(int y = y1; y < y2 + 1; y++){
	 light_toggle(lights, x, y, max_x);
      }
   }
}

void light_set(char *lights, char set, int x, int y, int max_x){
   *(lights+x*max_x+y) = set;
}

char light_get(char *lights, int x, int y, int max_x){
   return *(lights+x*max_x+y);
}

void light_toggle(char *lights, int x, int y, int max_x){
   lights = lights + x * max_x + y;

   *lights = *lights==1?0:1;
}

size_t light_count(char *lights, size_t count){
  size_t light_ct = 0;
  char *last_light = lights + count - 1;

  for(; lights < last_light + 1;)
     if(*lights++ == 1) light_ct++;

  return light_ct;
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

