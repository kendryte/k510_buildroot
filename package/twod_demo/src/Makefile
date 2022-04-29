CROSS_COMPILE:=riscv64-linux-

CC	:= $(CROSS_COMPILE)gcc
C++	:= $(CROSS_COMPILE)g++
OBJDUMP	:= $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
AR	:= $(CROSS_COMPILE)ar
AS	:= $(CROSS_COMPILE)as
LD	:= $(CROSS_COMPILE)gcc

ifeq ($(DEBUG),1)
	OPTIM   := -O0 -g3
else
	OPTIM   := -Os -g3
endif

PROG_1 = twod-rotation-app

PROG_2 = twod-scaler-app

### Verbosity control. Use 'make V=1' to get verbose builds.
V = 1
ifeq ($(V),1)
TRACE_CC  =
TRACE_C++ =
TRACE_LD  =
TRACE_AR  =
TRACE_AS  =
Q=
else
TRACE_CC  = @echo "  CC       " $<
TRACE_C++ = @echo "  C++      " $<
TRACE_LD  = @echo "  LD       " $@
TRACE_AR  = @echo "  AR       " $@
TRACE_AS  = @echo "  AS       " $<
Q=@
endif

all: ${PROG_1} ${PROG_2} ${PROG_3}
.PHONY: all

${PROG_1}: 
	${CC} -o ${PROG_1} lib_twod.c twod_rotation.c -I.
	@echo Completed

${PROG_2}:
	${CC} -o ${PROG_2} lib_twod.c twod_scaler.c -I.
	@echo Completed


.PHONY: printf
printf:
	@echo ${PROG_1}
	@echo ${PROG_2}


.PHONY: clean
clean:
	@rm ${PROG_1}
	@rm ${PROG_2}
