#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

static int test_nice(const char *d);

int main(int argc, char **argv){
   char test1[] = "ugknbfddgicrmopn";
   char test2[] = "aaa";
   char test3[] = "jchzalrnumimnmhp";
   char test4[] = "haegwjzuvuyypxyu";
   char test5[] = "dvszwmarrgswjxmb";

   printf("TEST: %20s: %s\n", test1, test_nice(test1)?"NICE":"NAUGHTY");
   printf("TEST: %20s: %s\n", test2, test_nice(test2)?"NICE":"NAUGHTY");
   printf("TEST: %20s: %s\n", test3, test_nice(test3)?"NICE":"NAUGHTY");
   printf("TEST: %20s: %s\n", test4, test_nice(test4)?"NICE":"NAUGHTY");
   printf("TEST: %20s: %s\n", test5, test_nice(test5)?"NICE":"NAUGHTY");

   return EXIT_SUCCESS;
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
