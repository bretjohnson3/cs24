.global my_setjmp
.global my_longjmp



my_setjmp:
    # saving all the callee save registers
    movq %rbp, (%rdi)
    movq %rbx, 8(%rdi)
    movq %rsp, 16(%rdi)
    movq %r12, 24(%rdi)
    movq %r13, 32(%rdi)
    movq %r14, 40(%rdi)
    movq %r15, 48(%rdi)
    movq (%rsp), %r8      # push return address
    movq %r8, 56(%rdi)
    movl $0, %eax
    ret


my_longjmp:
    # getting all of the callee save registers back
    movq (%rdi), %rbp
    movq 8(%rdi), %rbx
    movq 16(%rdi), %rsp
    movq 24(%rdi), %r12
    movq 32(%rdi), %r13
    movq 40(%rdi), %r14
    movq 48(%rdi), %r15

    movq 56(%rdi), %r8  # getting the return address back
    mov %r8, (%rsp)

    # do the correct behavior of the function (return argument or 1)
    mov $1, %eax
    test %esi, %esi
    cmovnz %esi, %eax
    ret
