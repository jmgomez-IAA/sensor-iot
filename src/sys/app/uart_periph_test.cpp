/**
 * @file uart_periph_test.cpp
 * @brief Enables the uart peripheral, and
 * transmit hello world.
 * @description The test-unit enables the UART1 peripheral
 * on the SAM4S device. It transmits the "Hello World" sentence
 * and each time it receive a byte, it binks the LED and
 * forwards it to the output.
 *
 *
 * The Configuration is Baudrate 9600, 8N1.
 * There is a makefile to build, Makefile-Uart_test.
 * make -f Makefile-Uart_test clean
 * make -f Makefile-Uart_test binary
 * sudo make -f Makefile-Uart_test flash
 *
 * For verification, a ttyUSB0 adaptor:
 * sudo screen 9600,cs0
 * Ctrl + a, k -> To exit.
 * To transmit to the device a char:
 * su
 * echo -ne '\33' > /dev/ttyUSB0
 *
 * @note No interruption, Fpck = 4 MHz.
 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>
#include <util/utility/util_time.h>

#include <array>

namespace{
  typedef util::timer<std::uint32_t> timer_type;
}

int main()
{

  mcal::init();

  const std::array<std::uint8_t, 10> send_buffer = {'H', 'o', 'l', 'a',' ', 'm','u', 'n', 'd', 'o'};
  unsigned char byte_to_receive = 0;

  while (1)
    {

      if ( mcal::uart::the_uart.receive_ready())
        {
          // LED OFF
          mcal::port::yellow_led_pin.set_pin_high();
          timer_type::blocking_delay(timer_type::seconds(1U));
          mcal::uart::the_uart.recv(byte_to_receive);
          // LED ON
          mcal::port::yellow_led_pin.set_pin_low();
          mcal::uart::the_uart.send(byte_to_receive);
          timer_type::blocking_delay(timer_type::seconds(1U));

        }

      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send_n( send_buffer.begin(), send_buffer.end());
      timer_type::blocking_delay(timer_type::milliseconds(100U));

    }

  //Wait forever.
  return 0;
}
