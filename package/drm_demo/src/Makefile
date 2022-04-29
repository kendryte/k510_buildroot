CROSS_COMPILE:=riscv64-linux-

CC	:= $(CROSS_COMPILE)gcc
C++	:= $(CROSS_COMPILE)g++
LD	:= $(CROSS_COMPILE)ld

DIRS := $(shell find -type d | grep -v .settings | grep -v Debug)
INCLUDES := $(addprefix -I , $(DIRS))
SRCS := $(foreach dir,$(DIRS) , $(wildcard $(dir)/*.c) $(wildcard $(dir)/*.cc) $(wildcard $(dir)/*.S) $(wildcard $(dir)/*.s))
OBJS := $(patsubst %.s,%.o,$(patsubst %.S,%.o,$(patsubst %.cc,%.o,$(patsubst %.c,%.o,$(SRCS)))))

CFLAGS = $(CFLAG) -Wall $(INCLUDES)
CXXFLAGS = $(CFLAGS)
ASFLAGS = -D__ASSEMBLY__ $(CFLAGS) -c
LDFLAGS = $(LDFLAG) -lstdc++ -lpthread

.SUFFIXES : %.o %.c %.cc %.S

%.o: %.c
	$(CC) -c -MMD $(CFLAGS) -o $@ $<

%.o: %.cc
	$(C++) -c -MMD $(CXXFLAGS) -o $@ $<

%.o: %.S
	$(CC) -c -MMD $(ASFLAGS) -o $@ $<

%.o: %.s
	$(CC) -c -MMD $(ASFLAGS) -o $@ $<

TARGET = drm_demo

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	@rm -f $(OBJS) $(OBJS:.o=.d) $(OBJS:.o=.gcda) $(OBJS:.o=.gcno)
	@rm -f $(TARGET)
