CROSS_COMPILE := riscv64-linux-
CC = $(CROSS_COMPILE)gcc
C++	:= $(CROSS_COMPILE)g++

SRCS = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRCS))

CFLAG = $(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include/libdrm -I$(STAGING_DIR)/usr/include/opencv4 -I$(STAGING_DIR)/usr/include
LDFLAG = -L$(STAGING_DIR)/usr/lib -ldrm -lnncase.runtime -lnncase.rt_modules.k510

CFLAGS = $(CFLAG) -Wall -fpic
LDFLAGS = $(LDFLAG) -lmppvo -lmppvi -lstdc++ -lpthread -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio

TARGET = sample_facedetect

all: $(TARGET)

$(TARGET): $(OBJ)
	$(C++) $^ $(LDFLAGS) -o $@

%.o: %.cc
	$(C++) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "clean object files done"

	@rm -f *~
	@echo "clean tempreator files done"

	@rm -f $(TARGET)
	@echo "clean target files done"

	@echo "clean done"