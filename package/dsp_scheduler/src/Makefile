CROSS_COMPILE := riscv64-unknown-elf-
TARGET ?=
MODE ?= evblp3
ifeq ($(MODE), evblp4)
EVBLP4 = 1
else ifeq ($(MODE), evblp3)
EVBLP3 = 1
else ifeq ($(MODE), fpga)
FPGA = 1
else ifeq ($(MODE), simu)
SIMU = 1
else
$(error the $(MODE) mode do not support! please set MODE=evblp4 or MODE=evblp3 or MODE=fpga or MODE=simu.)
endif

CC	:= $(CROSS_COMPILE)gcc
C++	:= $(CROSS_COMPILE)g++
OBJDUMP	:= $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
AR	:= $(CROSS_COMPILE)ar
AS	:= $(CROSS_COMPILE)as
LD	:= $(CROSS_COMPILE)gcc

DEBUG ?= 1
SIM_DDR ?= 1

ifeq ($(DEBUG),1)
	OPTIM   := -O0 -g3
else
	OPTIM   := -O3 -g3
endif

LDDIR = ./lds

PROG ?= scheduler
DIRS := .
DIRS += $(shell find ./tasks -type d | grep -v .settings |grep -v Debug)
DIRS += $(shell find $(STAGING_DIR)/usr/include/bsp -type d | grep -v .settings |grep -v Debug)
DIRS += $(shell find $(STAGING_DIR)/usr/include/audio3a -type d | grep -v .settings |grep -v Debug)

INCLUDES := $(addprefix -I, $(DIRS))
SRCS := $(foreach dir,$(DIRS) , $(wildcard $(dir)/*.c) $(wildcard $(dir)/*.cpp) $(wildcard $(dir)/*.S) $(wildcard $(dir)/*.s))
OBJS := $(patsubst %.s,%.o,$(patsubst %.S,%.o,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,${SRCS}))))

### Verbosity control. Use 'make V=1' to get verbose builds.
V := 0
ifneq ($(V),1)
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

CFLAGS += \
	-Wall $(OPTIM) $(INCLUDES) \
	-fomit-frame-pointer \
	-ffunction-sections -fdata-sections -matomic \
	-fno-zero-initialized-in-bss \
	-DCFG_MAKEFILE -mcpu=ax25 -mext-dsp \

ifeq ($(BR2_PACKAGE_DSP_SCHEDULER_AUDIO3A_TASK),y)
	CFLAGS += -DENABLE_AUDIO3A_TASK=\"$(BR2_PACKAGE_DSP_SCHEDULER_AUDIO3A_TASK)\"
	LIBS += -L $(STAGING_DIR)/lib64/lp64d -Wl,-Bstatic -laudio3a
else
	CFLAGS += -DENABLE_AUDIO3A_TASK=0
endif

ifneq ($(DSP_VECTOR), )
	CFLAGS += -DDSP_RESET_VECTOR=$(DSP_VECTOR)
endif

ifeq ($(DSP), 1)
	CFLAGS += -D_DSP
	LIBS += -ldsp
endif

#FPGA := 1
ifeq ($(FPGA), 1)
	CFLAGS += -D_FPGA
endif

LDSCRIPT ?= $(LDDIR)/k510.lds

ifeq ($(EVBLP4), 1)
	CFLAGS += -D_EVBLP4
endif

ifeq ($(EVBLP3), 1)
    CFLAGS += -D_EVBLP3
endif

ifeq ($(SIM_DDR), 1)
	CFLAGS += -D_SIM_DDR
endif

ifeq ($(DDR), 1)
ifeq ($(SIMU), 1)
	CFLAGS += -D_SIMU
endif
	LDSCRIPT = $(LDDIR)/k510_ddr.lds
else ifneq ($(DSPDIR), )
ifeq ($(SIMU), 1)
	CFLAGS += -D_SIMU
endif
else ifeq ($(SIMU), 1)
	CFLAGS += -D_SIMU
	LDSCRIPT = $(LDDIR)/k510_simu.lds
endif

ifeq ($(WAKEUP), 1)
LDSCRIPT = $(LDDIR)/k510_simu-wakeup.lds
endif

ifeq ($(LDTAR), sram1)
LDSCRIPT = $(LDDIR)/k510_sram1.lds
else ifeq ($(LDTAR), ddr)
LDSCRIPT = $(LDDIR)/k510_ddr.lds
else ifeq ($(LDTAR), poweron)
LDSCRIPT = $(LDDIR)/k510_simu-wakeup.lds
else ifeq ($(LDTAR), bootrom_start)
LDSCRIPT = $(LDDIR)/k510_bootrom_start.lds
endif

ifeq ($(DSPONLY), 1)
CFLAGS += -D_DSPONLY
endif

ifeq ($(RESUME), 1)
CFLAGS += -D_RESUME
endif

ifeq ($(CHIP_GLS_FFG), 1)
	CFLAGS += -DCHIP_GLS_FFG
endif
ifeq ($(CHIP_GLS_SSG), 1)
	CFLAGS += -DCHIP_GLS_SSG
endif
ifeq ($(CHIP_GLS_RTL), 1)
	CFLAGS += -DCHIP_GLS_RTL
endif

CXXFLAGS = $(CFLAGS)

ASFLAGS += -D__ASSEMBLY__ $(CFLAGS) -c

LDFLAGS += -T$(LDSCRIPT) $(OPTIM)  -static -nostartfiles -Wl,--gc-sections
#LDFLAGS += -T$(LDSCRIPT) $(OPTIM)  -static -Wl,--gc-sections

ifeq ($(LIBBSP), 1)
	LIBS		+= -Wl,--start-group -lm -lgcc -lc -mext-dsp
	LIBS	 	+= -Wl,--whole-archive $(LIBPATH)/libbsp.a -Wl,--no-whole-archive
	LIBS		+= -Wl,--end-group
	INCLUDES 	+= -I$(LIBBSPSRC)/include -I$(LIBBSPSRC)/include/controler/video
else
	LIBS		+= -lm -mext-dsp
	INCLUDES 	+= -I$(LIBBSPSRC)/include -I$(LIBBSPSRC)/include/controler/video
endif

LIBS += -L $(STAGING_DIR)/lib64/lp64d -Wl,-Bstatic -lbsp
LIBS += -L $(STAGING_DIR)/lib64/lp64d -Wl,-Bstatic -laudio3a

LDFLAGS += -mcmodel=medany
CFLAGS += -mcmodel=medany

all: $(PROG) $(LDSCRIPT)
# Compilation rules
.SUFFIXES : %.o %.c %.cpp %.S %.s

%.o: %.c
	$(TRACE_CC)
	$(Q)$(CC) -c -MMD $(CFLAGS) $(CEXTFLAGS) $(INCLUDES) $(LIBS) -o $@ $<
	@echo "Compiling $< ==> $@"

%.o: %.cpp
	$(TRACE_C++)
	$(Q)$(C++) -c -MMD $(CXXFLAGS) $(CEXTFLAGS) -o $@ $<

%.o: %.S
	$(TRACE_CC)
	$(Q)$(CC) -c -MMD $(ASFLAGS) $(CEXTFLAGS) -o $@ $<

%.o: %.s
	$(TRACE_CC)
	$(Q)$(CC) -c -MMD $(ASFLAGS) $(CEXTFLAGS) -o $@ $<

%.lds: %.ld	
	$(CC) -E  -Wp,-MD,-D__ASSEMBLY__  -DBR2_TARGET_EVB_FIRMWARE_LOAD_ADD=$(BR2_TARGET_EVB_FIRMWARE_LOAD_ADD) \
		-x assembler-with-cpp -std=c99 -P -o $@ $<
	@echo "Compiling lds"

$(PROG): $(OBJS)
	$(LD) -o $@.elf $(LDFLAGS) $(OBJS) $(LIBS)
	$(OBJCOPY) -O binary -S $(PROG).elf $(PROG).bin
	$(OBJDUMP) -S -x -d -C $(PROG).elf > $(PROG).asm

	@echo $(PROG) Completed

clean:
	rm -f *.o
	rm -f *.d
	rm -f $(OBJ)

	-rm -rf Debug
	-rm -f $(OBJS) $(OBJS:.o=.d) $(OBJS:.o=.gcda) $(OBJS:.o=.gcno)

	-rm -f *.elf
	-rm -f *.bin
	-rm -f *.asm
	-rm -f *.dat
	-rm -f *.list

# Automatic dependency generation
ifneq ($(MAKECMDGOALS),clean)
-include $(OBJS:.o=.d)
endif

