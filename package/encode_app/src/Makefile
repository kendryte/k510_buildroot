CROSS_COMPILE := riscv64-linux-

CC	:= $(CROSS_COMPILE)gcc
C++	:= $(CROSS_COMPILE)g++
OBJDUMP	:= $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
AR	:= $(CROSS_COMPILE)ar
AS	:= $(CROSS_COMPILE)as
LD	:= $(CROSS_COMPILE)gcc

CFLAGS = \
	-fomit-frame-pointer -fno-strict-aliasing -fno-builtin \
	-ffunction-sections -fdata-sections \
	-DCFG_MAKEFILE -DTARGET_BOARD_TYPE_def=\"$(BR2_TARGET_BOARD_TYPE)\"

OBJ ?= encode_app

$(OBJ): main.cpp video_app.cc G711Codec.cpp
	$(C++) $(CFLAGS) $^ -L ./ -Wl,-Bdynamic -lvenc -L ./ -Wl,-Bstatic -llive555 -L ./ -Wl,-Bdynamic -lmediactl -ladaptive -l3actl -L ./ -Wl,-Bdynamic -lvideo -L ./ -Wl,-Bdynamic -lasound -lstdc++ -Wl,-rpath . -lpthread -g -o $@

clean:
	rm -f *.o
	rm -f *.d
	rm -f $(OBJ)
