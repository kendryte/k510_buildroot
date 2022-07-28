CROSS_COMPILE = riscv64-linux-
CC=$(CROSS_COMPILE)g++

TARGET = v4l2_drm.out
OBJS = v4l2_drm.cc drm/k510_drm.c

all:
	${CC} ${OBJS} -I. -L. -L../ -fpermissive -Idrm -ldrm -lmediactl -lpthread -lstdc++ -g -o ${TARGET}
	@echo "Compile done."
clean:
	@rm -f *.o ${TARGET}
	@echo "Clean done."
