# The implementation of Eulers method for finding the GCD


.globl gcd

gcd:

    movl  %edi, %eax       # moving the n to the eax
    cqto
    idivl %esi             # divide a by b
    cmpl $0, %edx          # check if remainder is 0
    jne gcd_continue       # if not zero, go tot gcd_continue
    movl %esi, %eax        # else, move n to eax
    jmp gcd_return         # go to gcd_return

gcd_continue:

    movl %esi, %edi        # move n into edi, so that it becomes new m
    movl %edx, %esi        # remainder goes into esi so that it is new n
    call gcd               # recursive call

gcd_return:

    ret                    # break out of recursion
