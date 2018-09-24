#Declaration of Variables
EXE := hello
OBJS := t1.o t2.o main.o stubs.o
CFLAGS := -Wall -Werror -g -Og
LDFLAGS := -L/opt/mylibs
TARGET_ARCH := -mthumb
LDLIBS := -lm
CC := arm-none-eabi-gcc
VPATH = ./libs

all: $(EXE)

#Creation of the EXEC target
$(EXE): $(OBJS) 
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS)  -o $@

#Creation of the library stubs
stubs.o: stubs.c
	$(CC) -g -O2 $(TARGET_ARCH) -c -o $@ $<

-include $(subst .o,.d, $(SOURCES))
%.d : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M -MF $@ -MP $<

#Clean 
clean:
	rm -f $(EXE) $(OBJS) main.o stubs.o

.PHONY: all clean
