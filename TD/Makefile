# Board related tags and debugging
DRIVER = JLinkGDBServer  
DRIVER_TAGS = -endian little -if SWD -speed auto -ir -LocalhostOnly
DEVICE = -device STM32L475VG
DEBUGGER = arm-none-eabi-gdb
#Compiling
CC = arm-none-eabi-gcc -nostdlib -Wall -Wextra -Werror
CFLAGS = -g -O1
TARGET_ARCH = -mcpu=cortex-m4 -mthumb  -mfloat-abi=hard -mfpu=fpv4-sp-d16
#Assembling
AS = arm-none-eabi-as
ASFLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
#Link Edition and Libs to be included
LDFLAGS = -T
LOADLIBES = ld_ram.lds 
# Objects to be created
OBJS = main.o crt0.o init.o led.o
EXE = main

all : $(EXE) 

$(EXE) : $(LOADLIBES) $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

startgdbserver :
	$(DRIVER) $(DEVICE) $(DRIVER_TAGS)

debug :
	$(DEBUGGER) $(EXE)

clean:
	rm -f $(OBJS) $(EXE)
