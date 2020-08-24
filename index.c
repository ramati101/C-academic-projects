#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 50 /* max word length */

/*the struct of a node in binary tree, contain:
 a word, an array of the of lines that the word show up in,
 a counter that count in how many lines the word show up
 and poiners to the left and the right sons. */
typedef struct tnode  
{   
   char *pword; 
   int *pline;
   int count;
   struct tnode *left;
   struct tnode *right;
}tnode;

tnode *addtree(struct tnode *, char *, int);
void treeprint(FILE *, struct tnode *);

/* read from the file and create a new file
   with the all the words from the original file
   and make an index of the lines that every words
   show up in. */
int main(int argc, char *argv[])
{
   int input; 
   int line_ctr = 1;  /* line counter */
   char *word = (char*)calloc(MAXWORD,sizeof(char));
   int word_ctr = 0;  /* count the letter in the word */
   struct tnode *root = NULL;
   FILE *input_file;
   FILE *output_file;
   char *file_name;
   char end_name[7];
 
   
   if( argc != 2 )/* check if there is more or less than 1 argument */
   {
      fprintf(stderr, "only one argument allowed!(input file name)\n");
      exit(1);
   }

   /* create the name of the new file(the output file) */
   file_name = calloc((strlen(argv[1]))+10,sizeof(char));
   strcpy(file_name,argv[1]);
   strcpy(end_name,".index");
   strcat(file_name, end_name);
   
   /* check if the input file can be found */
   if( (input_file = fopen(argv[1], "r")) == NULL)
   {
      fprintf(stderr, "the input file is not exist\n");
      exit(1);
   }
   
   /* while loop get char by char till the end of file */
   while( (input=fgetc(input_file))!=EOF )
   {  
      if( isalnum(input) ) /* check if digit or alphabetic char */
      {   /* vv convert to lower-case and insert it to the char array */
         word[word_ctr++] = (char)(tolower(input)); 
         continue;
      }
      /* if the word array is empty and the char received isnt
         the new line */
      if( word_ctr == 0 && input != '\n' ) 
         continue;
      if( word_ctr != 0 )
      {
         word[word_ctr] = '\0'; /* put end to the string */
         root = addtree(root, word, line_ctr); /* add the node to binary tree */
         word_ctr = 0;      
      }
      if( input=='\n' ) 
         line_ctr++;
   }
   /* if the end of file is break the loop, but the word array isnt empty */
   if(word_ctr!=0)
   {
      word[word_ctr] = '\0'; 
      root = addtree(root, word, line_ctr);
   }
   fclose(input_file);

   output_file = fopen( file_name, "w" );

   treeprint(output_file, root); 
   fprintf(output_file, "\n");
   
   fclose(output_file);
   
   return 1;
}


char *strdup(char *);

struct tnode *addtree(struct tnode *p, char *w, int line)
{
   int cond;
   
   if(p == NULL)
   {
      p = (struct tnode *)malloc(sizeof(struct tnode));
      p->pword = strdup(w);
      p->pline = (int *)calloc(20,sizeof(int));
      p->count = 1;
      p->pline[p->count-1] = line;
      p->left = p->right = NULL;
   }
   else if( (cond = strcmp(w, p->pword)) == 0 )
   {
      if(p->pline[(p->count)-1]!=line)
      {
         p->pline[p->count] = line;
         p->count += 1;
      }
   }
   else if( cond < 0 )
      p->left = addtree(p->left, w, line);
   else
      p->right = addtree(p->right, w, line);
   return p;
}


char *strdup(char *s)
{
   char *p;

   p = (char *) malloc(strlen(s)+1);
   if(p != NULL)
      strcpy(p, s);
   return p;
}


void treeprint(FILE *out ,struct tnode *p)
{
   int i;
   int spaces;
   
   if(p != NULL)
   {
      treeprint(out, p->left);
      
      spaces = 13 - strlen(p->pword);
      fprintf(out,"%s",p->pword);
      for(i=0; i<spaces; i++)
            fprintf(out," ");
      if( p->count > 1 )
      {
         fprintf(out,"appears in lines ");
      for(i=0; i+1<p->count; i++)
         fprintf(out,"%d,", p->pline[i]);
      fprintf(out,"%d\n", p->pline[i]);
      }
      else
         fprintf(out,"appears in line  %d\n",p->pline[0]);
         
      treeprint(out, p->right);
   }
}







