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

ROOT = $(shell pwd)
PROG = $(shell pwd |sed 's/^\(.*\)[/]//' )

SRCDIR := srce
INCDIR := inc
LIBDIR := lib

SRCS := $(foreach dir,$(SRCDIR) , $(wildcard $(dir)/*.c) $(wildcard $(dir)/*.cpp) $(wildcard $(dir)/*.S) $(wildcard $(dir)/*.s))
OBJS := $(patsubst %.s,%.o,$(patsubst %.S,%.o,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,${SRCS}))))
$(info $(SRCS) $(OBJS))

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

# Common compilation options
CFLAGS = \
	-Wall $(OPTIM) -I$(INCDIR) \
	-fomit-frame-pointer -fno-strict-aliasing -fno-builtin \
	-ffunction-sections -fdata-sections -Wunused-function \
	-DCFG_MAKEFILE

CXXFLAGS = $(CFLAGS)

ASFLAGS = -D__ASSEMBLY__ $(CFLAGS) -c

LDFLAGS += -L$(LIBDIR) 
LIBS += -lpthread

# Compilation rules
.SUFFIXES : %.o %.c %.cpp %.S

all: $(PROG)

$(PROG): $(OBJS)
	$(Q)$(CC) $^ -o $@ $(LDFLAGS) $(LIBS)
	@echo Completed

%.o: %.c
	$(TRACE_CC)
	$(Q)$(CC) -c -MMD $^ -o $@ $(CFLAGS)

%.o: %.cpp
	$(TRACE_CC)
	$(Q)$(CC) -c -MMD $^ -o $@ $(CXXFLAGS)

%.o: %.S
	$(TRACE_CC)
	$(Q)$(CC) -c -MMD $(ASFLAGS) -o $@ $<

%.o: %.s
	$(TRACE_CC)
	$(Q)$(CC) -c -MMD $(ASFLAGS) -o $@ $<

.PHONY: clean
clean:
	@rm -rf $(PROG)
	@rm -f $(OBJS) $(OBJS:.o=.d) $(OBJS:.o=.gcda) $(OBJS:.o=.gcno)
	@rm -f $(PROG).out
	@rm -f $(PROG).bin
	@rm -f $(PROG).asm