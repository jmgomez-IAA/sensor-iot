#This Makefile should be modified to include multiple platform.
# Set some paths for the tools.

SRC_DIR = src/
BUILD_DIR = build/
BIN_DIR = bin/


#TOOL_PATH = /opt/gnu-mcu-eclipse/arm-none-eabi-gcc/7.2.1-1.1-20180401-0515/bin/
TOOL_PATH = /opt/gcc-arm-none-eabi-7-2018-q2-update/bin/
FLASH_PATH = /opt/edbg

# We are compiling for SAM4S CortexM4
ARCH = cortex-m4

# Compiler toolset
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
CINCLUDES = -Isrc -Isrc/mcal/sam4s -Isrc/util/STL -Isrc/sys/start/sam4s
LDFLAGS =  -mthumb  -Wl,--start-group -lm  -Wl,--end-group -L"./src/sys/start/sam4s"  -Wl,--gc-sections  -Tatsam4s16c.ld

SOURCES = src/sys/start/sam4s/crt0.cpp src/sys/start/sam4s/crt0_init_ram.cpp src/sys/start/sam4s/crt1.cpp src/sys/start/sam4s/int_vect.cpp src/mcal/mcal.cpp src/mcal/sam4s/mcal_cpu.cpp src/mcal/sam4s/mcal_irq.cpp src/mcal/sam4s/mcal_wdt.cpp  src/mcal/sam4s/mcal_port.cpp src/mcal/sam4s/mcal_gpt.cpp

#  src/mcal/sam4s/mcal_uart.cpp src/mcal/sam4s/mcal_i2c.cpp

OBJECTS = $(addprefix $(BUILD_DIR),$(patsubst %.cpp,%.o,$(SOURCES)))

PROGRAM = /src/sys/app/adc_periph_test.cpp /src/sys/app/sys_tick_chrono_test.cpp  /src/sys/app/blocking_delay_test.cpp  /src/sys/app/i2c_periph_test.cpp  /src/sys/app/software_interrupt_test.cpp  /src/sys/app/uart_periph_test.cpp  /src/sys/app/clock_source_test.cpp     /src/sys/app/pio_periph_test.cpp  /src/sys/app/sys_interval_test.cpp  /src/sys/app/yellow_led_test.cpp

.PHONY = all

all: yellow_led pio_periph sys_tick_chrono blocking_delay sys_interval i2c_periph uart_periph adc_periph eefc_periph modem_power
	echo "All done..."
	echo "sudo ${FLASH} -bpv -t atmel_cm4 -f bin/program_to_test.elf.bin"

yellow_led: $(BIN_DIR)yellow_led_test.elf
	echo "Building Yellow Led Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

sys_tick_chrono: $(BIN_DIR)sys_tick_chrono_test.elf
	echo "Building Systick Chrono Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

blocking_delay: $(BIN_DIR)blocking_delay_test.elf
	echo "Building Systick Chrono Blocking Delay Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

sys_interval: $(BIN_DIR)sys_interval_test.elf
	echo "Building System Tick Chrono Interval Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

pio_periph: $(BIN_DIR)pio_periph_test.elf
	echo "Building PIO  Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

modem_power: $(BIN_DIR)modem_power_test.elf
	echo "Building BGS2 Modem Power Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

eefc_periph:  $(BIN_DIR)eefc_periph_test.elf
	echo "Building Flash Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

i2c_periph: $(BIN_DIR)i2c_periph_test.elf
	echo "Building I2C Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

uart_periph: $(BIN_DIR)uart_periph_test.elf
	echo "Building UART Peripheral Test Program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

adc_periph: $(BIN_DIR)adc_periph_test
	echo "Building ADC Peripheral Test program."
	${OBJCOPY} -O ihex $^ $^.hex
	${OBJCOPY} -O binary $^ $^.bin

#Build Object files
$(BUILD_DIR)src/sys/start/sam4s/crt0.o:  src/sys/start/sam4s/crt0.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/start/sam4s/crt0_init_ram.o:  src/sys/start/sam4s/crt0_init_ram.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/start/sam4s/crt1.o:  src/sys/start/sam4s/crt1.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/start/sam4s/int_vect.o:  src/sys/start/sam4s/int_vect.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/mcal/mcal.o: src/mcal/mcal.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/mcal/sam4s/mcal_cpu.o: src/mcal/sam4s/mcal_cpu.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/mcal/sam4s/mcal_irq.o: src/mcal/sam4s/mcal_irq.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/mcal/sam4s/mcal_wdt.o: src/mcal/sam4s/mcal_wdt.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/mcal/sam4s/mcal_gpt.o: src/mcal/sam4s/mcal_gpt.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^


$(BUILD_DIR)src/mcal/sam4s/mcal_port.o: src/mcal/sam4s/mcal_port.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/mcal/sam4s/mcal_uart.o: src/mcal/sam4s/mcal_uart.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/mcal/sam4s/mcal_i2c.o: src/mcal/sam4s/mcal_i2c.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^


# Build the apps...
$(BUILD_DIR)src/sys/app/yellow_led_test.o:  src/sys/app/yellow_led_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/app/adc_periph_test.o:  src/sys/app/adc_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/app/sys_tick_chrono_test.o:  src/sys/app/sys_tick_chrono_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/app/blocking_delay_test.o:  src/sys/app/blocking_delay_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/app/pio_periph_test.o:  src/sys/app/pio_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/app/i2c_periph_test.o:  src/sys/app/i2c_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/app/uart_periph_test.o:  src/sys/app/uart_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/app/eefc_periph_test.o:  src/sys/app/eefc_periph_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)src/sys/app/sys_interval_test.o:  src/sys/app/sys_interval_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

$(BUILD_DIR)/src/sys/app/modem_power_test.o:  src/sys/app/modem_power_test.cpp
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^

# Link the apps
$(BIN_DIR)yellow_led_test.elf: $(OBJECTS) $(BUILD_DIR)src/sys/app/yellow_led_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/yellow_led_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)pio_periph_test.elf: $(OBJECTS) $(BUILD_DIR)src/sys/app/pio_periph_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/pio_periph_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)eefc_periph_test.elf: $(OBJECTS) $(BUILD_DIR)src/sys/app/eefc_periph_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/pio_periph_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list


$(BIN_DIR)adc_periph_test: $(OBJECTS) $(BUILD_DIR)src/sys/app/adc_periph_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/adc_periph_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)sys_interval_test.elf: $(OBJECTS) $(BUILD_DIR)src/sys/app/sys_interval_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/sys_interval_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)uart_periph_test.elf: $(OBJECTS) $(BUILD_DIR)src/sys/app/uart_periph_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/uart_periph_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)i2c_periph_test.elf: $(OBJECTS) $(BUILD_DIR)src/sys/app/i2c_periph_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/i2c_periph_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)blocking_delay_test.elf: $(OBJECTS) $(BUILD_DIR)src/sys/app/blocking_delay_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/blocking_delay_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list

$(BIN_DIR)sys_tick_chrono_test.elf: $(OBJECTS) $(BUILD_DIR)src/sys/app/sys_tick_chrono_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/sys_tick_chrono_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list



$(BIN_DIR)modem_power_test.elf: $(OBJECTS) $(BUILD_DIR)/src/sys/app/modem_power_test.o
	mkdir -p $(@D)
	${LD} -g $^ -o $@ -Wl,-Map="$(BUILD_DIR)src/sys/app/modem_power_test.map" $(LDFLAGS)
	${SIZE} $@
	${OBJDUMP} -D -S $@ > $@.list


# Upload the program to the memory of the device..
flash:
	${FLASH} -bpv -t atmel_cm4 -f bin/uart_periph_test.elf.bin

$(BUILD_DIR)%.o: src/%.c
	mkdir -p $(@D)
	${CXX} $(CXXFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $^


clean:
	rm bin build -rf
