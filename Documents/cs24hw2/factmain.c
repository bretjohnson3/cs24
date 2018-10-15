#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fact.h"


int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Usage: Incorrect number of arguements. Expected one integer\n");
    return 0;
  }
  int n = atoi(argv[1]);
  if (n < 0)
  {
    printf("Arguements must be non-negative!\n");
    return 0;
  }
  if (n == 0)
  {
    return 1;
  }
  else
  {
    printf("%d! equals %d\n", n, fact(n));
  }
}
