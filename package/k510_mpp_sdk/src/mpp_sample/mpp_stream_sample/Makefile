CROSS_COMPILE = riscv64-linux-
CC = $(CROSS_COMPILE)gcc
C++	:= $(CROSS_COMPILE)g++

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

CFLAG = $(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include
LDFLAG = -L$(STAGING_DIR)/lib64/lp64d -llive555 -L$(STAGING_DIR)/usr/lib

CFLAGS = $(CFLAG) -Wall -fpic
LDFLAGS = $(LDFLAG) -lmppvi -lmppsys -lmppvps -lmppvenc -lpthread

TARGET = sample_stream

all: $(TARGET)

$(TARGET): $(OBJ)
	$(C++) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(C++) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "clean object files done"

	@rm -f *~
	@echo "clean tempreator files done"

	@rm -f $(TARGET)
	@echo "clean target files done"

	@echo "clean done"