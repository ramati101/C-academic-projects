#include <stdio.h>
#include <stdlib.h>
/*
  the program gets input char by char, store every char in struct and
  linked them to linkedlist at the end of the input(when it read EOF char) 
  the program is printing all the input back to the standard output.
  and free the memory allocated.
*/

void main()
{
   int input;
   
   typedef struct element
   {
      char val;
      struct element *next;
   }elem;
   
   elem *curr, *head ,*pre;
   head = NULL;
   

   while( (input=getchar())!=EOF )
   {    /* get char after char till the EOF */
        /* put the char in elem struct */ 
      curr = (elem*)malloc(sizeof(elem));
      curr->val = (char)input;
      curr->next = NULL;
      
      if(head==NULL) /* if thats the first struct he is the head */
         head = curr;
      else      /* else, make the previous struct point on this struct */
         pre->next = curr;
      pre = curr;  /* make this struct the previous */

   }
   
   printf("\n");
   curr = head;
   while(curr)
   {
      printf("%c",curr->val);
      pre = curr;
      curr = curr->next;
      free(pre);
   }
   printf("\n");
}

