CROSS_COMPILE = riscv64-linux-
CC = $(CROSS_COMPILE)gcc

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

CFLAG = $(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include -I../mpp_common

CFLAGS = $(CFLAG) -Wall -fpic
LDFLAGS = -shared

TARGET = libmppvps.so

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
