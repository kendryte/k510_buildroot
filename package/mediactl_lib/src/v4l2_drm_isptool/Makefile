CROSS_COMPILE = riscv64-linux-
CC=$(CROSS_COMPILE)gcc

TARGET = v4l2_drm_isptool.out
OBJS = v4l2_drm_isptool.c ../v4l2_drm/drm/k510_drm.c ../v4l2_drm/sequeue.c

all:
	${CC} ${OBJS} -I../v4l2_drm/ -I../ -L. -L../ -I../v4l2_drm/drm -ldrm -lmediactl -lpthread -lstdc++ -o ${TARGET}
	@echo "Compile done."
clean:
	@rm -f *.o ${TARGET}
	@echo "Clean done."
