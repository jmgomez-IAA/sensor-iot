# Set some paths for the tools.

SRC_DIR = src/
#TOOL_PATH = /opt/gnu-mcu-eclipse/arm-none-eabi-gcc/7.2.1-1.1-20180401-0515/bin/
TOOL_PATH = /opt/gcc-arm-none-eabi-7-2018-q2-update/bin/
FLASH_PATH = /opt/edbg

# We are compiling for SAM4S CortexM4
ARCH = cortex-m4

# Compiler
CROSS_COMPILE = arm-none-eabi-
CXX = ${TOOL_PATH}/${CROSS_COMPILE}g++
LD = ${TOOL_PATH}/${CROSS_COMPILE}g++
OBJDUMP = ${TOOL_PATH}/${CROSS_COMPILE}objdump 
SIZE = ${TOOL_PATH}/${CROSS_COMPILE}size
OBJCOPY = ${TOOL_PATH}/${CROSS_COMPILE}objcopy
FLASH = ${FLASH_PATH}/edbg

# Compiler flags
INCLUDES = src/
LIBS = src/
CPPFLAGS = -mcpu=${ARCH} -g -O2 -Wall -Wextra -pedantic -fsigned-char -fno-exceptions
CXXFLAGS = -std=c++11
CINCLUDES = -Isrc -Isrc/mcal/sam4s
LDFLAGS = 



# Here is a simple Make Macro.
LINK_TARGET = bin/yellow_led.elf
HEX = bin/yellow_led.hex
BIN = bin/yellow_led.bin

# Here is a Make Macro that uses the backslash to extend to multiple lines.
SOURCES = src/mcal/mcal.cpp src/mcal/sam4s/mcal_led.cpp src/sys/start/yellow_led_test.cpp
OBJECTS = bin/mcal.o bin/mcal_led.o bin/yellow_led_test.o

.PHONY = all

all: bin/yellow_led.elf
	echo "All done..."

bin/mcal.o : src/mcal/mcal.cpp
	echo "Compile the mcal.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o bin/mcal.o -c src/mcal/mcal.cpp

bin/mcal_led.o : src/mcal/sam4s/mcal_led.cpp
	echo "Compile the mcal_led.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/yellow_led_test.o :  src/sys/app/yellow_led_test.cpp
	echo "Compile the mcal_led.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^


bin/yellow_led.elf : $(OBJECTS)
	echo "Link sources..."
	${LD} -g $^ -o $@
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(HEX) : $(LINK_TARGET)
	${OBJCOPY} -O ihex $^ $@.hex

$(BIN) : $(LINK_TARGET)
	${OBJCOPY} -O binary $^ $@.bin

# Upload the program to the memory of the device..
flash:
	${FLASH} -bpv -t atmel_cm4 -f bin/yellow_led.bin.bin

clean: 
	rm -f $(LINK_TARGET) $(OBJECTS)
	echo "Clean ... "

#ctr0:
#arm-none-eabi-g++ -mmcu=atmega328p -x assembler crt0.s -c -o bin/crt0.o

#compile:
#arm-none-eabi-g++ -mcpu=cortex-m4 -O2 -std=c++11 -I. -c src/sys/stub.cpp -o bin/stub.o
#arm-none-eabi-g++ -mcpu=cortex-m4 -O2 -std=c++11 -I. -c src/sys/start/ex0.cpp -o bin/ex0.o



#arm-none-eabi-g++ -mmcu=cortex-m4 bin/stub.o bin/ex0.o -o bin/ex0.elf

#assambler:
#arm-none-eabi-objdump -D -S bin/ex0.elf > ex0.list

#size:
#arm-none-eabi-size ex0.elf
