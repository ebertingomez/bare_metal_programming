CC = arm-none-eabi-gcc
CFLAGS = -g
LDFLAGS = --specs=nosys.specs

all: $(FILE)

%.o: %.c
	$(CC) $(CFLAGS) -O0 -c $< -o $@0.o
	$(CC) $(CFLAGS) -O1 -c $< -o $@1.o
	$(CC) $(CFLAGS) -O2 -c $< -o $@2.o

clean: 
	rm *.o