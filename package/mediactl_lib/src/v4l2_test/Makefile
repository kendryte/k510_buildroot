CROSS_COMPILE = riscv64-linux-
CC=$(CROSS_COMPILE)gcc

TARGET = v4l2_test.out
OBJS = v4l2_test.c

all:
	${CC} ${OBJS} -I. -L../ -lmediactl -lpthread -ladaptive -l3actl -lstdc++ -o ${TARGET}
	@echo "Compile done."
clean:
	@rm -f *.o ${TARGET}
	@echo "Clean done."
