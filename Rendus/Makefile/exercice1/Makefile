#Declaration of Variables
EXE := hello
OBJS := t1.o t2.o
FLAGS := -Wall -Werror -g -Og -c -o
COMMAND := arm-none-eabi-gcc -mthumb

all: $(EXE)

#Creation of the EXEC target
$(EXE): $(OBJS) main.o stubs.o
	$(COMMAND) -L/opt/mylibs $(OBJS) main.o stubs.o -lm -o $(EXE)

#Creation of the objects which require a header
$(OBJS): %.o : %.c %.h
	$(COMMAND) $(FLAGS) $@ $<

#Creation of  main
main.o: main.c
	$(COMMAND) $(FLAGS) $@ $<

#Creation of the library stubs
stubs.o: libs/stubs.c
	$(COMMAND) -g -O2 -c -o $@ $<

#Clean 
clean:
	rm -f $(EXE) $(OBJS) main.o stubs.o

.PHONY: all clean
