CROSS_COMPILE = riscv64-linux-
CC=$(CROSS_COMPILE)g++

all:
	${CC} v4l2_drm.cc drm/k510_drm.c -I. -I../ -L. -L../ -fpermissive -Idrm -ldrm -lmediactl -lpthread -lstdc++ -g -o v4l2_drm.out
	${CC} v4l2_drm_isptool.cc drm/k510_drm.c -I. -I../ -L. -L../ -fpermissive -Idrm -ldrm -lmediactl -lpthread -lstdc++ -g -o v4l2_drm_isptool.out
	@echo "Compile done."
clean:
	@rm -f *.o ${TARGET}
	@echo "Clean done."
