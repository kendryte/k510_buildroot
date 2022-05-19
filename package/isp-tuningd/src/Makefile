CROSS_COMPILE = riscv64-linux-
CC=$(CROSS_COMPILE)gcc

TARGET = isp-tuningd
OBJS = isp-tuningd.c

all:
	${CC} ${OBJS} -Wall -lpthread -luv -lvenc -o ${TARGET}
	@echo "Compile done."
clean:
	@rm -f *.o ${TARGET}
	@echo "Clean done."
