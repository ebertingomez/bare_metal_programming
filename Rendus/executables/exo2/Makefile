CC = gcc
CFLAGS = -g -O0
EXE = main
OBJS = main.o

all : $(EXE)

$(EXE): $(OBJS)
	$(LINK.o) $(OBJS)  -o $@

-include $(subst .o,.d, $(OBJS))

%.d : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M -MF $@ -MP $<

clean :
	-rm -r $(EXE)
	-rm -r *.o
	-rm -r *.d

.PHONY: all clean
