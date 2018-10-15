#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gcd.h"

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Usage: Incorrect number of command line arguements\n");
    return 0;
  }
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  if (m < 1 || n < 1)
  {
    printf("Usage: arguements must be non-negative");
    return 0;
  }
  /* ensures that the greater of the arguements is passed to gcd first */
  if (n > m)
  {
    int temp = m;
    m = n;
    n = temp;
  }
  printf("The GCD of (%d, %d) is %d\n", m, n, gcd(m,n));
}
