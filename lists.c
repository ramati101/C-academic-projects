#include <stdio.h>
#include <stdlib.h>
/*
  the program gets input char by char, store it in array of chars and if
  thats needed its enlarge the array with realloc function with more 10
  places, at the end of the input(when it read EOF char) the program
  is printing all the input back to the standard output.
*/

void main()
{
   int space = 10;
   int extraSpace = 10;
   int i;
   int p;
   int in;
   char *begin = (char *)calloc(space, sizeof(char)); /*array of 10 chars*/
   if(!begin)
   {
      printf("not enough memory");
      exit(1);
   }   


   for(i=0; ((in=getchar())!=EOF); i++)
   {
      *(begin+i)=(char)in;

      if(i==(space-1))
      {/* ^^if there is one place left free in the array,
                      \/\/enlarge it with realloc with 10 extra places */
         if(!(begin=(char *)realloc(begin, space+=extraSpace))) 
         {
            printf("not enough memory, the input is too long\n");
            exit(1);
         }
      }
   }
   
   printf("\n");
   for(p=0; p<i; p++)
   {
      printf("%c",*(begin+p));
   }
   printf("\n");

   free(begin);
}
