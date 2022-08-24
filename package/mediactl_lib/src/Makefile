ifdef MEDIACTL_LIB_PATH
	CUR_DIR=$(MEDIACTL_LIB_PATH)
else
	CUR_DIR=$(PWD)
endif

SRC = ${wildcard  isp/*.c} \
      ${wildcard  media/*.c} \
	  ${wildcard  v4l2/*.c} \
	  ${wildcard  *.c}

OBJ = ${patsubst %.c, %.o, ${SRC}}
TARGET = libmediactl.so

CROSS_COMPILE = riscv64-linux-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld

CCFLAGS=-g -Wall -lm -L./ -Iadaptive -ladaptive -I3actl -l3actl -O2

${TARGET}: ${OBJ}
	${LD} ${OBJ} -L./ -ladaptive -l3actl -shared  -o $@
	@echo "Compile done."

$(OBJ):%.o:%.c
	@echo "Compiling $< ==> $@"
	${CC} ${CCFLAGS} -c -fpic $< -o $@

clean:
	@rm -f ${OBJ}
	@echo "Clean object files done."

	@rm -f *~
	@echo "Clean tempreator files done."

	@rm -f ${TARGET}
	@echo "Clean target files done."

	@echo "Clean done."
