#include <stdio.h>
#include "../common/advent.h"
#include "../common/dary.h"
#include "../common/dstr.h"

#define INPUTFILE "input_day07.in"

typedef struct{
   char original[40];
   char instruction[10];
   char destination[10];
   char arg0[10];
   char arg1[10];
} inst_t;

void remove_lineending(char *buf);
void token_inst(inst_t *inst);
int isalpha(const char c);

int main(int argc, char **argv){
   FILE *fh;
   char buf[1024];
   errno_t errcode;
   int i;
   dynTarray instructions;
   dynTstr *str;
   inst_t *inst_list = 0;
   size_t instlist_sz;

   daryFinit(&instructions, (void(*)(void*)) &dstrFfree);

   fh=fopen(INPUTFILE,"r");
   //errcode = fopen_s(&fh, INPUTFILE, "r");

   if(!fh){
      printf("cannot open input file\n");
      exit(1);
   }

   while(fgets(buf, sizeof(buf), fh)){
      remove_lineending(buf);
      printf("%s\n", buf);
      str = malloc(sizeof(dynTstr));
      dstrFinit(str);
      dstrFappends(str, buf);
      daryFadd(&instructions, str);

      inst_list = realloc(inst_list, sizeof(inst_t) * ++instlist_sz);
      strcpy(inst_list[instlist_sz - 1].original, buf);
      token_inst(&inst_list[instlist_sz - 1]);
      inst_list[instlist_sz - 1].instruction[0] = 0;
      inst_list[instlist_sz - 1].destination[0] = 0;
      inst_list[instlist_sz - 1].arg0[0] = 0;
      inst_list[instlist_sz - 1].arg1[0] = 0;
   }
	
   printf("-------\n");
   printf("-------\n");

   for(i=0; i < instructions.cnt; i++)
      printf("%d:%s\n", i, ((dynTstr *) daryFget(&instructions,i))->strv);

   printf("\n");
   printf("\n");

   for(i = 0; i < instlist_sz; i++)
      printf("%d: [%s]: %s | %s | %s | %s\n", i, inst_list[i].original, inst_list[i].instruction, inst_list[i].destination, inst_list[i].arg0, inst_list[i].arg1);

   printf("\n");

   fclose(fh);
}


void remove_lineending(char *buf){
   while(*buf != 0){
      if(*buf == '\n')
         *buf = 0;
      else
         buf++;
   }
}

void token_inst(inst_t *inst){
   char *token = inst->original;
   char temp[10] = 0;
   char *temp_ptr = temp;

   if(isdigit(*token)){
      while(isdigit(*token)){
         *temp_ptr = *token++;
         if(tmp_ptr++ > temp + 9){
	    loggerf(ERRDEBUG, "BAD LINE: %s", inst->original);
            break;
         }
      }
      if(token != ' ' || token != 0)
         loggerf(ERRDEBUG, "BAD LINE: %s", inst->original);
      if(token == ' ')
         toekn++;

      strcpy(inst->arg0, temp);
   }
   
   if(isalpha(*token)){
      
   }
}

int isalpha(const char c){
   if(c > 'a' || c < 'z') return 1;
   if(c > 'A' || c < 'Z') return 1;
   return 0;
}
