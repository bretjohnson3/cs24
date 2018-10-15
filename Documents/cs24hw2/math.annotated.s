
/* This file contains x86-64 assembly-language implementations of three
 * basic, very common math operations.

 * The common theme of all these implementations is that they avoid branching.
   In each of these implementations, we could see why branching is a standard
   naive approach to the problem. In any of these functions, you could do some
   kind of check or comparison then branch somewhere if a condition holds and
   then perform an operation on the value there. These implementations all avoid
   branching in some way since branching is an expensive operation.
 */

        .text

/* returns the min of x and y. returns y if they are equal.

 * int f1(int x, int y)
 */
.globl f1
f1:
        movl    %edi, %edx #moves x to edx
        movl    %esi, %eax # moves y to eax
        cmpl    %edx, %eax # comparison of eax and edx. doing eax - edx
                              and updating flags accordingly
        cmovg   %edx, %eax # move if greater. Moves according to condition
                           # !(SF^OF) & !ZF
        ret


/* Absolute value function
 * int f2(int x)
 */
.globl f2
f2:
        movl    %edi, %eax # these lines move x into eax then into edx
        movl    %eax, %edx
        sarl    $31, %edx # shift right arithmetic 31 times. which if negative
                          # causes all ones. If 0 or positive is all 0s
        xorl    %edx, %eax # if x was positive or 0, xor won't chage it. If
                           # negative, will toggle all its bits
        subl    %edx, %eax # if x>= 0 return x, else return -x
        ret


/* Sign function. Returns 1 if positive, -1 if negative, 0 if 0.
 * int f3(int x)
 */
.globl f3
f3:
        movl    %edi, %edx # moves x to edx and eax
        movl    %edx, %eax
        sarl    $31, %eax  # arithemtic shift right. Gives all 0s if x>=0. else all 1s
        testl   %edx, %edx # Sets ZF=1 is x = 0 and SF = 1 if x < 0
        movl    $1, %edx   # moves 1 into edx
        cmovg   %edx, %eax # moves 1 to eax if neither flag is set (if x >0), else doesn;t move
        ret
