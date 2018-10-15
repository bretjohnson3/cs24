/*! \file
 *
 * This file contains definitions for an Arithmetic/Logic Unit of an
 * emulated processor.
 */


#include <stdio.h>
#include <stdlib.h>   /* malloc(), free() */
#include <string.h>   /* memset() */
#include <math.h>


#include "alu.h"
#include "instruction.h"


/*!
 * This function dynamically allocates and initializes the state for a new ALU
 * instance.  If allocation fails, the program is terminated.
 */
ALU * build_alu() {
    /* Try to allocate the ALU struct.  If this fails, report error then exit. */
    ALU *alu = malloc(sizeof(ALU));
    if (!alu) {
        fprintf(stderr, "Out of memory building an ALU!\n");
        exit(11);
    }

    /* Initialize all values in the ALU struct to 0. */
    memset(alu, 0, sizeof(ALU));
    return alu;
}


/*! This function frees the dynamically allocated ALU instance. */
void free_alu(ALU *alu) {
    free(alu);
}


/*!
 * This function implements the logic of the ALU.  It reads the inputs and
 * opcode, then sets the output accordingly.  Note that if the ALU does not
 * recognize the opcode, it should simply produce a zero result.
 */
void alu_eval(ALU *alu) {
    uint32_t A, B, aluop;
    uint32_t result;

    A = pin_read(alu->in1);
    B = pin_read(alu->in2);
    aluop = pin_read(alu->op);

    result = 0;

    switch (aluop)
    {
      //adds A and B
      case ALUOP_ADD:
          result = A + B;
          break;
      //Inverts the first arguement
      case ALUOP_INV:
          result = ~A;
          break;
      //Subtracts b from a
      case ALUOP_SUB:
          result = A - B;
          break;
      //XOR for a and b
      case ALUOP_XOR:
          result = A ^ B;
          break;
      //bitwise or for a and b
      case ALUOP_OR:
          result = (A | B);
          break;
      //increments a
      case ALUOP_INCR:
          result = A + 1;
          break;
      //bitwise and for a and b
      case ALUOP_AND:
          result = A & B;
          break;
      /*arithmetic shift right. only different from logical if arguement is
       negative */
      case ALUOP_SRA:
          //uint32_t first_b = pow(2, 31);

          if ((A & (uint32_t) pow(2, 31)) == 0)
          {
            result = A >> 1;
          }
          else
          {
            result = (A >> 1) | (uint32_t) pow(2, 31);
          }
          break;
      //logical shift right
      case ALUOP_SRL:
          result = A >> 1;
          break;
      //arithmetic shift left
      case ALUOP_SLA:
          result = A << 1;
          break;
      //logical shift left
      case ALUOP_SLL:
          result = A << 1;
          break;



    }

    pin_set(alu->out, result);
}
