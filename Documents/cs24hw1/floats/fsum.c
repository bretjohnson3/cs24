#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "ffunc.h"


/* This function takes an array of single-precision floating point values,
 * and computes a sum in the order of the inputs.  Very simple.
 */
float fsum(FloatArray *floats) {
    float sum = 0;
    int i;

    for (i = 0; i < floats->count; i++)
        sum += floats->values[i];

    return sum;
}


float my_fsum(FloatArray *floats)
{
  int i;
  float sum = 0;

  // Setting Base case to sum naively once array is sufficiently small
  if (floats->count <= 2)
  {
    for (i = 0; i < floats->count; i++)
    {
      sum += floats->values[i];

    }
  }
    // If the array not small enough split in half
    else
    {
      int size;
      int right_size;


      // This if-else pair was used since the floor function wasn't working
      if (floats->count % 2 == 0)
      {
        size = floats->count / 2;
        right_size = size;
      }
      else
      {
        size = ((floats->count - 1) / 2);
        right_size = size + 1;
      }

      // initializng
      FloatArray *left = malloc(sizeof(FloatArray));
      FloatArray *right = malloc(sizeof(FloatArray));

      left->count = size;
      right->count = right_size;
      //printf("%d, %d\n",size, right_size);

      left->values = malloc(sizeof(float) * size);
      right->values = malloc(sizeof(float)* right_size);

      // Filling the left side
      for (i = 0; i < size; i++)
      {
        //printf("%d\n", i);
        left->values[i] = floats->values[i];
      }

      // Filling the right side
      for (i = 0; i < right_size; i++)
      {
        //printf("%d\n", i + right_size);
        right->values[i] = floats->values[size + i];
      }

      sum = my_fsum(left) + my_fsum(right);
      //printf("%e\n", sum);
      free(left->values);
      free(right->values);
      free(left);
      free(right);
    }
  return sum;
}


int main() {
    FloatArray floats;
    float sum1, sum2, sum3, my_sum;

    load_floats(stdin, &floats);
    printf("Loaded %d floats from stdin.\n", floats.count);

    /* Compute a sum, in the order of input. */
    sum1 = fsum(&floats);

    /* Use my_fsum() to compute a sum of the values.  Ideally, your
     * summation function won't be affected by the order of the input floats.
     */

    my_sum = my_fsum(&floats);

    /* Compute a sum, in order of increasing magnitude. */
    sort_incmag(&floats);
    sum2 = fsum(&floats);

    /* Compute a sum, in order of decreasing magnitude. */
    sort_decmag(&floats);
    sum3 = fsum(&floats);

    /* %e prints the floating-point value in full precision,
     * using scientific notation.
     */
    printf("Sum computed in order of input:  %e\n", sum1);
    printf("Sum computed in order of increasing magnitude:  %e\n", sum2);
    printf("Sum computed in order of decreasing magnitude:  %e\n", sum3);

    printf("My sum:  %e\n", my_sum);


    return 0;
}
