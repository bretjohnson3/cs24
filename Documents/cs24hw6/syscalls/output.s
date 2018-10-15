.global output

# This function takes in a message and the size of the message and
# traps into the kernel in order to

# message is in rdi and the size of the message is in rsi.
# unistd_64.h says: #define __NR_write 1

output:
    movq    $1  , %rax    # move the system call number into rax
    movq    %rsi, %rdx    # move the size of the message into argument slot 2
    movq    %rdi, %rsi    # move the the actual message into argument slot 3
    movq    $1  , %rdi    # move the file descriptor for stdout into arg 1

    syscall               # invoke system call

    retq                  # yay
