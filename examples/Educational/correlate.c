#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sTime
{
   char *name;
   double time;
};

struct sTime *ReadTimes(const char *path)
{
   char buffer[1024];
   FILE *fp = fopen(path, "r");
   if(fp)
   {
      int N = 0;
      while(fgets(buffer, 1024, fp))
         N++;
      struct sTime *rval = (struct sTime *) malloc((N+1) * sizeof(struct sTime));
      rewind(fp);
      N = 0;
      while(fgets(buffer, 1024, fp))
      {
         if(strncmp("Def Cons:", buffer, 8) && (' ' != *buffer))
         {
            char *p = strchr(buffer, ' ');
            if(p && (p != buffer))
            {
               *p = '\0';
               rval[N  ].name = _strdup(buffer);
               rval[N++].time = atof(p+1);
            }
         }
      }
      rval[N].name = NULL;
      rval[N].time = 0.;
      fclose(fp);
      return rval;
   }
   else
   {
      fprintf(stderr, "Couldn't open %s\n", path);
      exit(-1);
   }
   return NULL;
}

void Destroy(struct sTime *data)
{
   if(data)
   {
      for(int i = 0 ; data[i].name ; i++)
         free(data[i].name);
      free(data);
   }
}

int main(int argc, char *argv[])
{
   char *first  = "III.txt";
   char *second = "IV.txt";
   if(argc > 2)
   {
      first  = argv[1];
      second = argv[2];
   }
      
   struct sTime *III = ReadTimes(first );
   struct sTime *IV  = ReadTimes(second);
   if(III && IV)
   {
      printf("                           %s\t%s\n", first, second);
      double timeIII = 0.;
      double timeIV  = 0.;
      int IIIwins    = 0;
      int IVwins     = 0;
      int i = 0 ; 
      for( ; III[i].name && IV[i].name ; i++)
      {
         if(!_stricmp(III[i].name, IV[i].name))
         {
            if(III[i].time == IV[i].time)
            {
               printf("%25s: %g\t%g\n", III[i].name, III[i].time, IV[i].time);
            }
            else if(III[i].time < IV[i].time)
            {
               printf("%25s: [%g]\t%g\n", III[i].name, III[i].time, IV[i].time);
               IIIwins++;
            }
            else if(III[i].time > IV[i].time)
            {
               printf("%25s: %g\t[%g]\n", III[i].name, III[i].time, IV[i].time);
               IVwins++;
            }
            else
               printf(" internal error\n");

            timeIII += III[i].time;
            timeIV  +=  IV[i].time;
         }
         else
            printf("diff: %s vs %s\n", III[i].name, IV[i].name);
      }
      if(III[i].name || IV[i].name)
      {
         printf("unmatched: %s\n", III[i].name ? III[i].name : IV[i].name);
      }
      printf("                     wins: %d\t%d\n", IIIwins, IVwins);
      printf("                    total: %g\t%g\n", timeIII , timeIV);
   }
   Destroy(III);
   Destroy(IV );
   return 0;
}