#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int main(int argc, char *argv[])
{
   SayHello();
   SayIAmHere();
   SayBye();

   return(0);
}
