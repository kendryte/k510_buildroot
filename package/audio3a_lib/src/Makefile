CUR_DIR=$(PWD)
INCLUDES += -I../bsp/include -I./AGC -I./NS -I./wy_aec/include/speex -I./wy_aec/libspeex -I./include 

SRC = $(wildcard ./AGC/*.c) \
	   $(wildcard ./NS/*.c) \
       $(wildcard ./wy_aec/libspeex/*.c) \
	   audio3a.c

OBJ = ${patsubst %.c, %.o, ${SRC}}
DSP_OBJ = ${patsubst %.c, %.o, ${SRC}}

TARGET?=
# DSP_LIB=libaudio3a.a

CROSS_COMPILE=riscv64-linux-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld

CCFLAGS=-g -Wall ${INCLUDES} -L ./ -O2
# .so for linux #
ifeq ($(TARGET), libaudio3a.so)
$(shell rm ${DSP_OBJ})
${TARGET}: ${OBJ}
	${LD} ${OBJ} -shared  -o $@
	@echo "Compile done."

$(OBJ):%.o:%.c
	@echo "Compiling $< ==> $@"
	${CC} ${CCFLAGS} -c -fpic $< -o $@

# .a for dsp #
else ifeq ($(TARGET), libaudio3a.a)
DSP_CROSS_COMPILE=riscv64-unknown-elf-
DSP_CC	:= $(DSP_CROSS_COMPILE)gcc
DSP_C++	:= $(DSP_CROSS_COMPILE)g++
DSP_OBJDUMP	:= $(DSP_CROSS_COMPILE)objdump
DSP_OBJCOPY := $(DSP_CROSS_COMPILE)objcopy
DSP_AR	:= $(DSP_CROSS_COMPILE)ar
DSP_AS	:= $(DSP_CROSS_COMPILE)as
LDSP_D	:= $(DSP_CROSS_COMPILE)gcc

$(shell rm ${OBJ})

# ${DSP_LIB}: ${DSP_OBJ}
${TARGET}: ${DSP_OBJ}
	@echo "DSP_OBJ $(DSP_OBJ)"
	${DSP_AR} cr $@ ${DSP_OBJ}
	@echo "DSP compile done."

${DSP_OBJ}:%.o:%.c
	@echo "DSP compiling $< ==> $@"
	${DSP_CC} ${CCFLAGS} -c -fpic $< -o $@
endif

clean:
	@rm -f ${OBJ} ${DSP_OBJ}
	@echo "Clean object files done."

	@rm -f *~
	@echo "Clean tempreator files done."

	@rm -f ${TARGET} ${DSP_LIB}
	@echo "Clean target files done."

	@echo "Clean done."


