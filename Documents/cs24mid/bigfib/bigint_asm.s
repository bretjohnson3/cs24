# Function for __add_bigint from bigint.c written in x86-64 assembly code.
# The function implements the addition of two bigints. It takes in three
# arguements: a bigint* a, a bigint* b, and the size of the bigints.
# The function returns 1 if size == 0. Otherwise, it performs the addition.
# If the addition results in an on overflow, the function returns zero.
# Otherwise, it returns 1.

.global __add_bigint

# a is in rdi, b is rsi, size in rdx


__add_bigint:
    movq    %rdx, %r8                # set up decrementing loop variable in r8
    movq    %rdi, %r9                # put a in r9
    movq    %rsi, %r10               # put b in r10
    clc                              # clear carry flag before adding

__add_bigint_size_check:
    cmpq   $0, %r8                          # check if the size is zero
    jz     __add_bigint_return_size_zero    # move to return_size_zero


__add_bigint_add_loop:
    movq   (%r9), %r11                   # move the current value at a to r11
    adcq   %r11, (%r10)                  # add with carry b[i] += a[i]
    leaq   8(%r9), %r9                   # now pointing at the next value in a
    leaq   8(%r10), %r10                 # now pointing at the next value in b
    decq   %r8                           # decrememnt loop variable
    jnz    __add_bigint_add_loop         # break out of loop if loop has been
                                         # done size - 1 times


__add_bigint_check_overflow:
    jc    __add_bigint_return_zero     # check if carry flag set from last add
    movq  $1, %rax                     # return 1 if addition succesful
    ret

__add_bigint_return_zero:
    movq $0, %rax                      # return zero if not successful 
    ret


__add_bigint_return_size_zero:
    movq $1, %rax
    ret
