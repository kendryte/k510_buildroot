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

PROG_3 = twod-scaler-overlay-osd-app

PROG_4 = twod-osd2yuv-app

PROG_5 =  twod-scaler-output-rgb888-app

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

all: ${PROG_1} ${PROG_2} ${PROG_3} ${PROG_4} ${PROG_5}
.PHONY: all

${PROG_1}: 
	${CC} -o ${PROG_1} lib_twod.c twod_rotation.c -I.
	@echo Completed

${PROG_2}:
	${CC} -o ${PROG_2} lib_twod.c twod_scaler.c -I.
	@echo Completed

${PROG_3}:
	${CC} -o ${PROG_3} lib_twod.c twod_scaler_overlay_osd.c -I.
	@echo Completed

${PROG_4}:
	${CC} -o ${PROG_4} lib_twod.c twod_rgb2yuv.c -I.
	@echo Completed

${PROG_5}:
	${CC} -o ${PROG_5} lib_twod.c twod_scaler_output_rgb888.c -I.
	@echo Completed

.PHONY: printf
printf:
	@echo ${PROG_1}
	@echo ${PROG_2}
	@echo ${PROG_3}
	@echo ${PROG_4}
	@echo ${PROG_5}


.PHONY: clean
clean:
	@rm ${PROG_1}
	@rm ${PROG_2}
	@rm ${PROG_3}
	@rm ${PROG_4}
	@rm ${PROG_5}
