# Set some paths for the tools.

SRC_DIR = src/
#TOOL_PATH = /opt/gnu-mcu-eclipse/arm-none-eabi-gcc/7.2.1-1.1-20180401-0515/bin/
TOOL_PATH = /opt/gcc-arm-none-eabi-7-2018-q2-update/bin/
FLASH_PATH = /srv/share/Workspace/ARM/resources/edbg

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
CPPFLAGS = -mmcu=${ARCH} -O2 
CXXFLAGS = -std=c++11
LDFLAGS = 

# Here is a simple Make Macro.
LINK_TARGET = bin/ex0.elf
HEX = bin/ex0.hex
BIN = bin/ex0.bin

# Here is a Make Macro that uses the backslash to extend to multiple lines.
OBJS =  \
 bin/ex0.o \

.PHONY = all $(HEX) $(BIN)

all:  $(LINK_TARGET) 
	echo "All done..."

# Here is a Rule that uses some built-in Make Macros in its command:
# $@ expands to the rule's target, in this case "test_me.exe".
# $^ expands to the rule's dependencies, in this case the three files
# main.o, test1.o, and  test2.o.
$(LINK_TARGET) : ${OBJS}
	echo "Link sources..."
	${LD} -g $^ -o $@
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

#link without std_lib:
#arm-none-eabi-g++ -mmcu=cortex-m4 -nostartfiles -nostdlib -Wl,-Tavr.ld,-Map,bin/led.map bin/led.o bin/crt0.o -o bin/led.elf

# Compile de .cpp file to .o
# $@ for the pattern-matched target
# $< for the pattern-matched dependency
%.o : %.cpp
	echo "Compile sources..."
	${CXX} -g -o $@ -c $<

bin/ex0.o : src/sys/start/ex0.cpp
	echo "Specific target compilation."
	${CXX} -g -o $@ -c $<

$(HEX) : $(LINK_TARGET)
	${OBJCOPY} -O ihex $^ $@.hex

$(BIN) : $(LINK_TARGET)
	${OBJCOPY} -O binary $^ $@..bin

# Upload the program to the memory of the device..
flash:
	${EDBG} -bpv -t atmel_cm4 -f bin/ex0.bin

clean: 
	rm -f $(TARGET) $(OBJS)
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
