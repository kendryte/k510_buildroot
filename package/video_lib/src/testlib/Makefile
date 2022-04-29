CROSS_COMPILE=riscv64-linux-
CC=$(CROSS_COMPILE)gcc

TARGET=test_videolib

OBJS=test_videolib.cc

all:
	${CC} ${OBJS} -I../ -L../ -lpthread -lvideo -lstdc++ -o ${TARGET}
	@echo "Compile done."

clean:
	@rm -f *o ${TARGET}
	@echo "Clean done."


