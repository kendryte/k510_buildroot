CROSS_COMPILE=riscv64-linux-
CC=$(CROSS_COMPILE)gcc

TARGET=test_videolib_n

OBJS=test_videolib_n.cc

TARGET1=test_dualcamera

OBJS1=test_dualcamera.cc

TARGET2=tunning_server_hdmi

OBJS2=tunning_server_hdmi.cc

TARGET3=tunning_server_dsi

OBJS3=tunning_server_dsi.cc

TARGET4=test_scamera

OBJS4=test_scamera.cc

all:
	${CC} ${OBJS} -I../ -L../ -lvideo -lstdc++ -o ${TARGET}
	${CC} ${OBJS1} -I../ -L../ -lvideo -lstdc++ -o ${TARGET1}
	${CC} ${OBJS2} -I../ -L../ -lvideo -lpthread -lstdc++ -o ${TARGET2}
	${CC} ${OBJS3} -I../ -L../ -lvideo -lpthread -lstdc++ -o ${TARGET3}
	${CC} ${OBJS4} -I../ -L../ -lvideo -lpthread -lstdc++ -o ${TARGET4}
	@echo "Compile done."

clean:
	@rm -f *o ${TARGET} ${TARGET1} ${TARGET2} ${TARGET3} ${TARGET4}
	@echo "Clean done."


