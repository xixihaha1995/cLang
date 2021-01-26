OBJS=main.o tool1.o tool2.o
CC=gcc
CFLAGS+= -c -Wall -g

mytool:$(OBJS)
	$(CC) $^ -o $@
	# all .o to mytool
%.o:%.c
	$(CC) $^ $(CFLAGS) -o $@
	# all .c to .o
clean:
	$(RM) *.o mytool -r