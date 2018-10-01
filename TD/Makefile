TERMINAL = gnome-terminal --

DRIVER = JLinkGDBServer  
DRIVER_TAGS = -endian little -if SWD -speed auto -ir -LocalhostOnly
DEVICE = -device STM32L475VG
DEBUGGER = arm-none-eabi-gdb

CC = arm-none-eabi-gcc
CFLAGS = -g -O1 
TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS = -T
LOADLIBES = ld_ram.lds 
OBJS = main.o
EXE = main
LINK.o = $(CC) $(LDFLAGS) -o $(EXE)

$(EXE) : $(OBJS) $(LOADLIBES)

all : $(EXE)

debug :
	$(TERMINAL) $(DRIVER) $(DEVICE) $(DRIVER_TAGS)
	$(DEBUGGER) $(FILE)
clean:
	rm -f $(OBJS) $(EXE)
