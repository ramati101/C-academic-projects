#include <stdio.h>
#include <math.h>
#define PI 3.141592653589793

/* the method gets a angle in radians and return the cos of this angle
*/

double my_cos(double x)
{
   double element = 1;
   double sum = 1;
   double i = 2;
   double fact = 1;
   double mult = 1;
   int sign = 1;

   while( (element = (mult*=x*x)/(fact*=((i-1)*(i))))>0.000001 )
   {
      sign *= -1;
      sum += sign * element;
      i += 2;
   }

   return sum;
}

int main()
{
   int angle;
   double rad;
   int circle = 360;

   printf("please enter an angle\n");
   scanf("%d", &angle);

   angle = fmod(angle, circle); 
   rad = angle*(PI/180); /* convert from degree to radian */
   
   printf("\nmy_cos is:%f \nmath.h cos is:%f \n",my_cos(rad),cos(rad));
   
   return 1;
}



