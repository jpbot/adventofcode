#include <stdio.h>
#include "../common/advent.h"
#include "../common/dary.h"
#include "../common/dstr.h"

#define INPUTFILE "input_day07.in"

int main(int argc, char **argv){
   FILE *fh;
   char buf[1024];
   errno_t errcode;
   int i;
   dynTarray instructions;
   dynTstr *str;

   daryFinit(&instructions, (void(*)(void*)) &dstrFfree);

   fh=fopen(INPUTFILE,"r");
   //errcode = fopen_s(&fh, INPUTFILE, "r");

   if(!fh){
      printf("cannot open input file\n");
      exit(1);
   }

   while(fgets(buf, sizeof(buf), fh)){
      printf("%s", buf);
      str = malloc(sizeof(dynTstr));
      dstrFinit(str);
      dstrFappends(str, buf);
      daryFadd(&instructions, str);


   }
	
   printf("-------");
   printf("-------");

   for(i=0; i < instructions.cnt; i++)
      printf("%d:%s\n", i, ((dynTstr *) daryFget(&instructions,i))->strv);

   printf("\n");

   fclose(fh);
}


