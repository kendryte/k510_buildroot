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

OBJ ?= alsa_demo

$(OBJ): alsa_demo.c
	$(C++) $(CFLAGS) $^ -L ./ -Wl,-Bdynamic -lasound -g -o $@
	
clean:
	rm -f *.o
	rm -f *.d
	rm -f $(OBJ)

