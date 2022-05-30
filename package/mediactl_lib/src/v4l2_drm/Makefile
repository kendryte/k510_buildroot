CROSS_COMPILE = riscv64-linux-
CC=$(CROSS_COMPILE)gcc

TARGET = v4l2_drm.out
OBJS = v4l2_drm.c drm/k510_drm.c

all:
	${CC} ${OBJS} -I. -L. -L../ -Idrm -ldrm -lmediactl -lpthread -lstdc++ -o ${TARGET}
	@echo "Compile done."
clean:
	@rm -f *.o ${TARGET}
	@echo "Clean done."