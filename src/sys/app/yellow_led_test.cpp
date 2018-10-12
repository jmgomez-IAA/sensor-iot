/**
 * @file yellow_led_test.cpp
 * @brief Drives the yellow led and the Switch buttom of the board.
 * @description Configures, the board and makes the Yellow LED connected
 * to the PC23 pin blinks. On the other side, the Sw0, connected to the
 * PA02 pin when pressed, stops the LED from blinking.
 *
 * @note The UART is used to transmit some debug information, about the
 * PIO A Controller status.
 *
 *
 * The Configuration for the UART is Baudrate 9600, 8N1.
 * There is a makefile to build, Makefile-Uart_test.
 * make -f clean
 * make -f binary
 * sudo make flash
 *
 * For verification, a ttyUSB0 adaptor:
 * sudo screen 9600,cs0
 * Ctrl + a, k -> To exit.

 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>
#include <util/utility/util_time.h>

namespace{
  typedef util::timer<std::uint32_t> timer_type;
}

int main()
{
  mcal::init();

  while (1)
    {
      //LWS OFF
      mcal::port::led1_pin.set_pin_high();
      mcal::port::led2_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::seconds(1U));

      // LED ON
      mcal::port::led1_pin.set_pin_low();
      mcal::port::led2_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::seconds(1U));

    }


  //Wait forever.
  return 0;
}
