.file	"example.c"
.text
.globl	ex
.type	ex, @function
ex:
.LFB0:
.cfi_startproc


# Starts here

pushq	%rbp              # Pushes register rbp onto the stack
.cfi_def_cfa_offset 16
.cfi_offset 6, -16
movq	%rsp, %rbp        # moves data at rsp to rbp
.cfi_def_cfa_register 6
movl	%edi, -20(%rbp)   # moves double-word register edi into M[-20 + %rbp]
                        # this is moving a

movl	%esi, -24(%rbp)   # moves double-word register esi into M[-24 + %rbp]
                        # this is moving b

movl	%edx, -28(%rbp)   # moves double-word register esi into M[-28 + %rbp]
                        # this is moving c

movl	%ecx, -32(%rbp)   # moves double-word register ecx into M[-32 + %rbp]
                        # this is moving d

movl	-24(%rbp), %eax   # moves double-word M[-24 + %rbp] into %eax
                        # i.e. moving b into eax
subl	-28(%rbp), %eax   # setting value at %eax to itself - the value at
                        # M[-28 + %rbp]. This is doing b - c and storing at %eax

imull	-20(%rbp), %eax   # multiplying M[-20 + %rbp] by value at %eax which is
                        # a multiplying the value at %eax which is b-c and
                        # storing at %eax
                        # THIS IS WHERE THE * OCCURS

movl	%eax, %edx        # moves M[eax] to %edx -> moving a * (b-c) to %edx
movl	-32(%rbp), %eax   # moving double-word at M[-32 + %rbp] which is input d
                        # to %eax
addl	%edx, %eax        # adds %edx to %eax which is adding d to a*(b-c)

movl	%eax, -4(%rbp)
movl	-4(%rbp), %eax
popq	%rbp
.cfi_def_cfa 7, 8
ret
.cfi_endproc
.LFE0:
.size	ex, .-ex
.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
.section	.note.GNU-stack,"",@progbits
