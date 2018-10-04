CC = arm-none-eabi-gcc
CFLAGS = -g
LDFLAGS := -L/opt/mylibs
TARGET_ARCH := -mthumb
VPATH = ./libs
OBJS = stubs.o file1.o file2.o file3.o file4.o

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -Os -c $< -o $@s.o
	$(CC) $(CFLAGS) -O0 -c $< -o $@0.o
	$(CC) $(CFLAGS) -O1 -c $< -o $@1.o
	$(CC) $(CFLAGS) -O2 -c $< -o $@2.o

stubs.o: stubs.c
	$(CC) -g -O2 $(TARGET_ARCH) -c -o $@ $<

clean:
	rm -f $(OBJS)

.PHONY: all clean