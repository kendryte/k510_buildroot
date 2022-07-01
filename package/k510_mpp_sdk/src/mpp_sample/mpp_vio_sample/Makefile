CROSS_COMPILE = riscv64-linux-
CC = $(CROSS_COMPILE)gcc

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

CFLAG = $(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include/libdrm -I$(STAGING_DIR)/usr/include
LDFLAG = -L$(STAGING_DIR)/usr/lib -ldrm

CFLAGS = $(CFLAG) -Wall -fpic
LDFLAGS = $(LDFLAG) -lmppvi -lmppvo -lmppsys -lmppvps

TARGET = sample_vio

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "clean object files done"

	@rm -f *~
	@echo "clean tempreator files done"

	@rm -f $(TARGET)
	@echo "clean target files done"

	@echo "clean done"