// DAY 20  -  lowest house number with n presents

#include "../common/advent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
   unsigned long presents, house, elf;
   unsigned long target  = PUZZLEINPUTDAY20;
   unsigned long targettenth = target / 10;
   unsigned long *houses;

   loggerf(ERRDEBUG, "input: %lu", target);

   houses = malloc(sizeof(unsigned long) * (targettenth + 1));

   if(houses){
      loggerf(ERRDEBUG, "allocated %lu * %d bytes for buffer.", (targettenth + 1), sizeof(unsigned long));
   } else {
      loggerf(ERRFATAL, "could not allocate buffer");
      return EXIT_FAILURE;
   }

   //------------------------------------------------------------------
   //PART -A
   //------------------------------------------------------------------
   memset(houses, 0, sizeof(unsigned long) * (targettenth + 1));

   for(elf = 1; elf <= targettenth; elf++){
      for(house = elf; house <= targettenth; house += elf){
         houses[house] += elf;
      }
   }

   for(house = 1; house <= targettenth; house++){
      if(houses[house] >= targettenth){
         loggerf(ERRINFO, "PART A: FOUND HOUSE NUMBER: %lu", house);
         break;
      }
   }

   //------------------------------------------------------------------
   //PART - B
   //------------------------------------------------------------------
   memset(houses, 0, sizeof(unsigned long) * (targettenth + 1));

   for(elf = 1; elf <= targettenth; elf++){
      presents = 0;
      for(house = elf; house <= targettenth; house += elf){
         houses[house] += (elf * 11);
         if(++presents == 50) break;
      }
   }

   for(house = 1; house <= targettenth; house++){
      if(houses[house] >= target){
         loggerf(ERRINFO, "PART B: FOUND HOUSE NUMBER: %lu", house);
         break;
      }
   }

   return EXIT_SUCCESS;
}
