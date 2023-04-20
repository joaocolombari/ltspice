#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   int rval = 0;
   char buffer[4096] = { 0 };
   for(int i = 1 ; i < argc ; i++)
   {
      FILE *fp = fopen(argv[i], "r");
      if(fp)
      {
         while(fgets(buffer, sizeof(buffer)-1, fp))
         {
            if(!strncmp(buffer, "TEXT ", 5))
            {
               int font = 0;
               sscanf(buffer, "TEXT %*d %*d %*s %d", &font);
               if(2 != font)
               {
                  rval++;
                  printf("%s: %s", argv[i], buffer);
               }
            }
            *buffer = '\0';
         }
         fclose(fp);
      }
      else
         fprintf(stderr, "couldn't open %s\n", argv[i]);
   }
   return rval;
}
