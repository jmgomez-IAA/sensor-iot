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


# Here is a simple Make Macro.
LINK_TARGET = bin/yellow_led.elf
HEX = bin/yellow_led.elf.hex
BIN = bin/yellow_led.elf.bin

# Compiler flags
INCLUDES = src/
LIBS = src/
CPPFLAGS = -mcpu=${ARCH} -g -O2 -Wall -Wextra -pedantic -fsigned-char -fno-exceptions
CXXFLAGS = -std=c++11
CINCLUDES = -Isrc -Isrc/mcal/sam4s -Isrc/sys/start/sam4s -Isrc/util/utility
LDFLAGS =  -mthumb -Wl,-Map="yellow_led.map" -Wl,--start-group -lm  -Wl,--end-group -L"./src/sys/start/sam4s"  -Wl,--gc-sections  -Tatsam4sd32c.ld

# Here is a Make Macro that uses the backslash to extend to multiple lines.
SOURCES = src/sys/start/sam4s/crt0.cpp src/sys/start/sam4s/crt0_init_ram.cpp src/sys/start/sam4s/crt1.cpp src/sys/start/sam4s/int_vect.cpp src/mcal/mcal.cpp src/mcal/sam4s/mcal_cpu.cpp src/mcal/sam4s/mcal_irq.cpp  src/mcal/sam4s/mcal_port.cpp src/mcal/sam4s/mcal_uart.cpp src/mcal/sam4s/mcal_i2c.cpp src/mcal/sam4s/mcal_gpt.cpp src/mcal/sam4s/mcal_wdt.cpp src/mcal/sam4s/mcal_led.cpp src/sys/start/yellow_led_test.cpp
OBJECTS = bin/crt0.o bin/crt0_init_ram.o bin/crt1.o bin/int_vect.o bin/mcal.o bin/mcal_cpu.o bin/mcal_irq.o bin/mcal_port.o bin/mcal_uart.o bin/mcal_i2c.o bin/mcal_gpt.o bin/mcal_wdt.o bin/mcal_led.o

.PHONY = all

all: bin/yellow_led.elf bin/pio_periph.elf  bin/i2c_periph.elf
	echo "All done..."

bin/yellow_led.elf : $(OBJECTS) bin/yellow_led_test.o
	echo "Link sources..."
	${LD} -g $^  -o $@ $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

bin/pio_periph.elf : $(OBJECTS) bin/pio_periph.o
	echo "Link PIO Periph Test Unit..."
	${LD} -g $^  -o $@ $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

bin/i2c_periph.elf : $(OBJECTS) bin/i2c_periph.o
	echo "Link i2c Periph Test Unit..."
	${LD} -g $^  -o $@ $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list



bin/crt0.o : src/sys/start/sam4s/crt0.cpp
	echo "Compile the crt0.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o bin/crt0.o -c src/sys/start/sam4s/crt0.cpp

bin/crt0_init_ram.o : src/sys/start/sam4s/crt0_init_ram.cpp
	echo "Compile the crt0_init_ram.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o bin/crt0_init_ram.o -c src/sys/start/sam4s/crt0_init_ram.cpp

bin/crt1.o : src/sys/start/sam4s/crt1.cpp
	echo "Compile the crt1.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o bin/crt1.o -c src/sys/start/sam4s/crt1.cpp

bin/int_vect.o : src/sys/start/sam4s/int_vect.cpp
	echo "Compile the int_vect.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o bin/int_vect.o -c src/sys/start/sam4s/int_vect.cpp

bin/mcal.o : src/mcal/mcal.cpp
	echo "Compile the mcal.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o bin/mcal.o -c src/mcal/mcal.cpp

bin/mcal_cpu.o : src/mcal/sam4s/mcal_cpu.cpp
	echo "Compile the mcal_cpu.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/mcal_gpt.o : src/mcal/sam4s/mcal_gpt.cpp
	echo "Compile the mcal_gpt.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/mcal_port.o : src/mcal/sam4s/mcal_port.cpp
	echo "Compile the mcal_port.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/mcal_irq.o : src/mcal/sam4s/mcal_irq.cpp
	echo "Compile the mcal_irq.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/mcal_uart.o : src/mcal/sam4s/mcal_uart.cpp
	echo "Compile the mcal_uart.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/mcal_i2c.o : src/mcal/sam4s/mcal_i2c.cpp
	echo "Compile the mcal_i2c.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/mcal_wdt.o : src/mcal/sam4s/mcal_wdt.cpp
	echo "Compile the mcal_wdt.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/mcal_led.o : src/mcal/sam4s/mcal_led.cpp
	echo "Compile the mcal_led.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/yellow_led_test.o :  src/sys/app/yellow_led_test.cpp
	echo "Compile the mcal_led.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/pio_periph.o :  src/sys/app/pio_periph_test.cpp
	echo "Compile the pio_periph_test.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

bin/i2c_periph.o :  src/sys/app/i2c_periph_test.cpp
	echo "Compile the pio_periph_test.cpp"
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^


$(HEX) : $(LINK_TARGET)
	${OBJCOPY} -O ihex $^ $@.hex

binary : $(LINK_TARGET)
	${OBJCOPY} -O binary $^ $^.bin

# Upload the program to the memory of the device..
flash:
	${FLASH} -bpv -t atmel_cm4 -f bin/yellow_led.elf.bin

bin/pio_periph.elf.bin : bin/pio_periph.elf
	/opt/gcc-arm-none-eabi-7-2018-q2-update/bin//arm-none-eabi-objcopy -O binary bin/pio_periph.elf bin/pio_periph.elf.bin

flash_pio_periph : bin/pio_periph.elf.bin
	/opt/edbg/edbg -bpv -t atmel_cm4 -f bin/pio_periph.elf.bin

bin/i2c_periph.elf.bin : bin/i2c_periph.elf
	/opt/gcc-arm-none-eabi-7-2018-q2-update/bin//arm-none-eabi-objcopy -O binary bin/i2c_periph.elf bin/i2c_periph.elf.bin

flash_i2c_periph : bin/i2c_periph.elf.bin
	/opt/edbg/edbg -bpv -t atmel_cm4 -f bin/i2c_periph.elf.bin


clean: 
	rm -f bin/*
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
