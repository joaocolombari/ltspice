#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

void AddSymbol(char ***List, int *N, int *Nmax, char *buffer)
{
   char **list = *List;
   if(!list)
   {
      *Nmax = 16;
      list = (char **) malloc(*Nmax * sizeof(char *));
   }
   else if(N+2 >= Nmax)
   {
      *Nmax *= 2;
      list = (char **) realloc(list, *Nmax * sizeof(char *));
   }
   list[*N] = _strdup(buffer);
   *N       = *N + 1;
   list[*N] = NULL;
   *List    = list;
}

char **LTsymbolList(const char *name)
{
   char base[MAX_PATH];
   char path[MAX_PATH];
   char **list = NULL;
   int Nmax    = 0;
   int N       = 0;
   strcpy(path, name);
   char *p = strrchr(path, '.');
   if(!_stricmp(p, ".asc"))
      *p = '\0';
   strcpy(base, path);
   strcat(path, ".asc");
   FILE *fp = fopen(path, "r");
   if(fp)
   {
      char buffer[4096];
      while(fgets(buffer, 4096, fp))
      {
         if(!strncmp(buffer, "SYMBOL ", 7))
         {
            char *p = strchr(buffer+7, 'L'); // could be an LT, LTC, or LTM number
            if(p)
            {
               char *q = strchr(p, ' ');
               if(q)
               {
                  *q = '\0'; // truncate
                  char *u = strrchr(p, '\\');
                  if(u)
                     p = u + 1;
                  if((*p == 'L') && strstr(p, base))
                  {
                     AddSymbol(&list, &N, &Nmax, p);
                  }
               }
            }
         }
      }
      fclose(fp);
   }
   return list;
}

int main(int argc, char *argv[])
{
   for(int j = 1 ; j < argc ; j++)
   {
      char **list = LTsymbolList(argv[j]);
      printf("%s ->", argv[j]);
      if(list)
      {
         int i = 0;
         while(list[i])
         {
            printf(" \"%s\"", list[i]);
            free(list[i]);
            i++;
         }
         free(list);
      }
      printf("\n");
   }
   return 0;
}
