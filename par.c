#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100
/* the program check if the input code in C is valid in aspect of brackets
   
   the program is pass char after char and check that:
   -there is no more than one of { or } in the same row, and they the last char in the row(except \n).
   -the brackets { and } are balanced in the all code.
   -the brackets [] and () are balanced in the same row.
   -the program ignore what wrote in note(like this one) and in "quotation mark"
   -the program use LIFO array for the []() so for the last bracket have to get is    close same bracket first.
    
   assumption:
   -there isnt note after { or } in the same row. 
   -row max length is 100.  */


int main()
{
   char brack[MAXLENGTH] = {'\0'}; /* Last in First Out array of opening brackets  */
   int i = 0;
   int curlybefore = 0;
   int countcurly = 0;
   char lastcurly;
   char current;
   int r=0;
   int slash = 0;
   int star = 0;
   int secstar = 0;
   int apost = 0;
   int line = 1;
   char problem = '0';
   char linestr[MAXLENGTH] = {'\0'}; /* array of chars for the row with the problem */
   

   while((current=getchar())!=EOF && problem=='0')
   {
      linestr[r++]=current;

      if((apost==1 && current!='\"') || (slash==1 && star==1 && secstar==0 && current!='*')) /* if we are in a note like this one or in apostrophes */ continue;

      if(curlybefore!=0 && current!='\n') /* if the last char was { or } and the line isnt ended */
      {   
         problem = lastcurly;
         break;
      }

      if(current=='\n' && brack[0]!='\0') /* if the line ends but the stack arent empty */
      {
         problem = brack[0];
         break;
      }

      if(slash==1 && star==0 && current!='*') /* if there is slash but the current char isnt star */   slash--;

      if(slash==1 && star==1 && secstar==1 && current!='/') /* if there is slash and two stars but the current char isnt slash */ 
      {
         secstar--;
         continue;
      }
    

      switch(current)
      {
         case '{': curlybefore = 1;
                   countcurly++;
                   lastcurly = '{';
                   break;

         case '}': curlybefore = 1;
                   countcurly--;
                   lastcurly = '}';
                   break;

         case '[': brack[i++] = '[';
                   break;
 
         case '(': brack[i++] = '(';
                   break;

         case ']': if(i==0 || brack[i-1]!='[')
                   {
                      problem = ']';
                      break;
                   }
                   brack[--i] = '\0';
                   break;

         case ')': if(i==0 || brack[i-1]!='(')
                   {
                      problem = ')';
                      break;
                   }
                   brack[--i] = '\0';
                   break;
   
         case '/': if(slash==0)
                   {
                      slash++;
                      break;
                   }
                   if(slash==1 && star==1 && secstar==1)
                   {
                      slash--;
                      star--;
                      secstar--;
                      break;
                   }
                   

         case '*': if(slash==1 && star==1)
                      secstar++;
                   else if(slash==1)
                      star++;
                   break;

         case '"': if(apost==1) 
                      apost--;
                   else 
                      apost++;
                   break;

         case '\n': curlybefore = 0;
                    line++;
                    r = 0;
                    break;
         }
   }
       if(problem!='0') /**/
       {
          linestr[r] = '\0'; /* puts end to the string */
          printf("there is a problem in line: %d \nwith the sign: %c \n here is the line: %s \n",line ,problem ,linestr);
       }
       else
           printf("there is no problems in the input code\n");

  return 0;
                    

                   
}
