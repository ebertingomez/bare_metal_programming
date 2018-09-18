EXE := hello
OBJS := t1.o t2.o
FLAGS := -Wall -Werror -g -Og -c -o
COMMAND := arm-none-eabi-gcc -mthumb

all: $(EXE)

$(EXE): $(OBJS) main.o stubs.o
	$(COMMAND) -L/opt/mylibs $(OBJS) main.o stubs.o -lm -o $(EXE)

$(OBJS): %.o : %.c %.h
	$(COMMAND) $(FLAGS) $@ $<

main.o: main.c
	$(COMMAND) $(FLAGS) $@ $<

stubs.o: libs/stubs.c
	$(COMMAND) -g -O2 -c -o $@ $<

clean:
	rm -f $(EXE) $(OBJS) main.o stubs.o

.PHONY: all clean
