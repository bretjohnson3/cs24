OBJS = c_except.o my_setjmp.o ptr_vector.o divider.o

CFLAGS=-g
ASFLAGS=-g

test_setjmp: my_setjmp.o test_setjmp.o
	gcc -g -o test_setjmp my_setjmp.o test_setjmp.o

divider : $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@


ptr_vector.c : ptr_vector.h
c_except.c : c_except.h my_setjmp.h
divider.c : c_except.h my_setjmp.h
my_setjmp.o: my_setjmp.s
test_setjmp.o: my_setjmp.h test_setjmp.c

check: test_setjmp
	./test_setjmp

clean :
	rm -f *.o *~ divider divider.exe test_setjmp my_setjmp
