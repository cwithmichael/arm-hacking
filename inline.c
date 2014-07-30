#include <stdio.h>

int main()
{
   char result[12];
   asm __volatile__
    (
     "xor %%eax, %%eax;"
     "cpuid;"
     "mov %%ebx, %0;"
     "mov %%edx, %1;"
     "mov %%ecx, %2;"
     :
     :"m"((result)), 
      "m"(*(result+4)), "m"(*(result+8))
    );
   printf("The Vendor ID is\n", result);
}
