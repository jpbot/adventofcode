#include <CommonCrypto/CommonDigest.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "input.h"

#define MD5_DIGEST_LENGTH 16

static const char * md5hash(const char *d, int len, char *hash);
static int check_advent(const char *d);

int main(int argc, char **argv){
   char buffer[33] = {0};
   char md5buffer[33] = {0};
   char *bufnum;
   char test1[20] = "pqrstuv1048970";
   char test2[20] = "abcdef609043";
   unsigned long ac_dec = 1;
   size_t base_len, dec_len;

   printf("input: %s\n", PUZZLEINPUTDAY4);
   printf("'%s' md5: %s", test1, md5hash(test1, strlen(test1), buffer));
   if(check_advent(buffer)){
      printf(": AdventCoin!\n");
   } else {
      printf("\n");
   }
   printf("'%s' md5: %s", test2, md5hash(test2, strlen(test2), buffer));
   if(check_advent(buffer)){
      printf(": AdventCoin!\n");
   } else {
      printf("\n");
   }

   base_len = strlen(PUZZLEINPUTDAY4);
   memcpy(buffer, PUZZLEINPUTDAY4, base_len);
   bufnum = buffer + base_len;

   do{
      if(++ac_dec ==0){
         printf("ERROR, overflow on unsigned long.\n");
         exit(EXIT_FAILURE);
      }

      dec_len = sprintf(bufnum, "%lu", ac_dec);
      md5hash(buffer, base_len + dec_len, md5buffer);
      printf("base_len: %lu dec_len:%lu total:%lu  buffer:%s  hash:%s\n", base_len, dec_len, base_len + dec_len, buffer, md5buffer);
   } while(check_advent(md5buffer) == 0);

   return EXIT_SUCCESS;
}

static int check_advent(const char *d){
   static int i;

   for(i = 0; i < 5; i++)
      if(d[i] != '0')
         return 0;

   return 1;
}

static const char * md5hash(const char *d, int len, char *hash){
   int i;
   static char buffer[33] = {0};
   unsigned char digest[16];

   CC_MD5(d, len, digest);

   for(i = 0; i < 16; i++)
      sprintf(buffer + 2 * i, "%02x", digest[i]);

   if(hash){
      memcpy(hash, buffer, 33);
      return hash;
   }

   return buffer;
}
