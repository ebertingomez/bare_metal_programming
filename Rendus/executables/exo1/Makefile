CC = arm-none-eabi-gcc
CFLAGS = -g -O1
LDFLAGS = -L/opt/mylibs
TARGET_ARCH :=
VPATH = ./libs
OBJS := stubs.o


all: $(FILE)

$(FILE) : $(FILE).o $(OBJS)

stubs.o: stubs.c
	$(CC) -g -O2 $(TARGET_ARCH) -c -o $@ $<

-include $(subst .o,.d, $(OBJS))

%.d : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M -MF $@ -MP $<

clean: 
	rm *.o

.PHONY: all clean