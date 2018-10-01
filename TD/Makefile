DRIVER =JLinkGDBServer  
DRIVER_TAGS =-endian little -if SWD -speed auto -ir -LocalhostOnly
DEVICE =-device STM32L475VG
DEBUGGER =arm-none-eabi-gdb
TERMINAL =gnome-terminal --

debug :
	$(TERMINAL) $(DRIVER) $(DEVICE) $(DRIVER_TAGS)
	$(DEBUGGER) $(FILE)
