// crt_sprintf_s.c
// This program uses sprintf_s to format various
// data and place them in the string named buffer.
//

#include <stdio.h>

int main( void )
{
   char  buffer[200], s[] = "computer", c = 'l';
   int   i = 35, j;
   float fp = 1.7320534f;

   // Format and print various data: 
   j  = sprintf_s( buffer, 200,     "   String:    %s\n", s );
   j += sprintf_s( buffer + j, 200 - j, "   Character: %c\n", c );
   j += sprintf_s( buffer + j, 200 - j, "   Integer:   %d\n", i );
   j += sprintf_s( buffer + j, 200 - j, "   Real:      %f\n", fp );

   char* p="I love China";
   j += sprintf_s( buffer + j, 200 - j, "   I add:     %s\n", p);

   char a[200];
   //j = sprintf_s(a, 200, "%s", p);
   j = sprintf_s(a, 13, "%s", p);
   printf_s("%s %d\n", a, j);

   //printf_s( "Output:\n%s\ncharacter count = %d\n", buffer, j );
}
