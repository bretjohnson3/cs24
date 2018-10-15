#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "my_setjmp.h"


static jmp_buf buffer;

/* A test to check that setjmp returns the second arguement when the second
* arguement is not 0 in longjmp
*/
int not_zero(int a)
{
    int b = setjmp(buffer);
    switch(b)
    {
        case 0:
            longjmp(buffer, a);
        default:
            if (b == a)
            {
              return 1;
            }
    }
    return 0;
}
// Test to check that setjmp returns 1 when longjmp has 0 arguement
int zero_test()
{
  switch(setjmp(buffer))
  {
    case 0:
        longjmp(buffer, 0);
    case 1:
        return 1;
    default:
        return 0;
  }
}
// function to use in test_nest to test levels of function calls
int nester()
{
  int x = 3;
  x += 1;
  if (x < 10)
  {
    longjmp(buffer, 1);
  }
  return x;
}
// Tests two levels of function calls
int test_nest()
{
  switch(setjmp(buffer))
  {
      case 0:
          nester();
      case 1:
          return 1;
      default:
          return 0;
  }
}

// Test for stack corruption
int stack(int x, int y)
{
    int z;
    switch(setjmp(buffer))
    {
        case 0:
            z = x + y;
            longjmp(buffer, 0);
        case 1:
            if (z == x + y)
            {
                return 1;
            }
        default:
            return 0;
    }
}

int main()
{
  printf("Test for longjmp returning arguement when it doesnt equal 0\n");
  int a = 85;
  printf("Test should produce %d\n", a);
  if (not_zero(a) == 1)
  {
      printf("PASS\n");
  }
  else
  {
      printf("FAIL\n");
  }

  printf("Test longjmp returns 0 when arguement is 0\n");
  if (zero_test() == 1)
  {
      printf("PASS\n");
  }
  else
  {
      printf("FAIL\n");
  }

  printf("Testing longjmp over two layers of function calls\n");
  if (test_nest() == 1)
  {
      printf("PASS\n");
  }
  else
  {
      printf("FAIL\n");
  }

  printf("Testing for stack corruption on call of longjmp\n");
  int x = 6;
  int y = 8;
  if (stack(x, y) == 1)
  {
      printf("PASS\n");
  }
  else
  {
      printf("FAIL\n");
  }
  return 0;
}
