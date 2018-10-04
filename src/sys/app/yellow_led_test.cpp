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
      mcal::port::yellow_led_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::seconds(1U));

      // LED ON
      mcal::port::yellow_led_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::seconds(1U));

      volatile std::uint32_t sw0_enable_status;
      sw0_enable_status = mcal::reg::access< std::uint32_t,
                                          std::uint32_t,
                                          static_cast<std::uint32_t>(0x400E0E00)>::reg_get();

      if ( sw0_enable_status & (0x1 << 2) )
        mcal::uart::the_uart.send( 'E' );
      else
        mcal::uart::the_uart.send( 'D' );

      timer_type::blocking_delay(timer_type::milliseconds(100U));

      volatile std::uint32_t sw0_output_status;
      sw0_output_status = mcal::reg::access< std::uint32_t,
                                             std::uint32_t,
                                             static_cast<std::uint32_t>(0x400E0E18)>::reg_get();

      if ( sw0_output_status & (0x1 << 2) )
        mcal::uart::the_uart.send( 'O' );
      else
        mcal::uart::the_uart.send( 'I' );

      timer_type::blocking_delay(timer_type::milliseconds(100U));
      volatile std::uint32_t pio_reg_status;
      pio_reg_status = mcal::reg::access< std::uint32_t,
                                          std::uint32_t,
                                          static_cast<std::uint32_t>(0x400E0E3C)>::reg_get();


      timer_type::blocking_delay(timer_type::milliseconds(100U));
      if ( pio_reg_status & (0x1 << 2) )
        mcal::uart::the_uart.send( '1' );
      else
        mcal::uart::the_uart.send( '0' );

      while(! mcal::port::sw0_button_pin.read_input_value() )
        {
          mcal::cpu::nop();
          timer_type::blocking_delay(timer_type::milliseconds(100U));
          mcal::uart::the_uart.send( '0' );
        }
    }


  //Wait forever.
  return 0;
}
