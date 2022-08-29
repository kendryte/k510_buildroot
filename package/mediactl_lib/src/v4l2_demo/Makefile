CROSS_COMPILE = riscv64-linux-
CC=$(CROSS_COMPILE)gcc

TARGET = v4l2-demo

OBJS = v4l2-demo.c  v4l2.c

TARGET = v4l2-demo

all:
	${CC} ${OBJS} -I../ -L../ -lpthread -lmediactl -ladaptive -l3actl -lstdc++ -o ${TARGET}
	@echo "Compile done."
clean:
	@rm -f *o ${TARGET}
	@echo "Clean done."