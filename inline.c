#include <stdio.h>

int main()
{
   char result[12];
   asm __volatile__
    (
     "xor %%eax, %%eax\n"
     "cpuid\n"
     "movl %%ebx, %0\n"
     "movl %%edx, %1\n"
     "movl %%ecx, %2\n"
     :
     :"m"((result)), 
      "m"(*(result+4)), "m"(*(result+8))
    );
   printf("The Vendor ID is %s\n", result);
}
