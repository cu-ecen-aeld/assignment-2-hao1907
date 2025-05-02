#  native compilation
CC = gcc
CFLAGS = -Wall -Wextra -static

#CROSS_COMPILE = aarch64-none-linux-gnu-
#  cross-compilation
ifdef CROSS_COMPILE
    CC := $(CROSS_COMPILE)gcc
endif

# Name of the target executable
TARGET = writer

# Default target
all: $(TARGET)

# Build writer
$(TARGET): writer.o
	$(CC) $(CFLAGS) -o $@ $^

writer.o: writer.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Target clean
clean:
	rm -f $(TARGET) *.o

# Phony targets
.PHONY: all clean