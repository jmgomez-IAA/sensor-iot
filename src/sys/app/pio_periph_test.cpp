/**
 * @file pio_periph_test.cpp
 * @brief Manages the PIO Controller of the SAM4S processor.
 * @description Blinks the Yellow LED of the SAM4S Xaplainned
 * board (PC23). When the Switch button SW0 (PA2) is pressed/released
 * the an ISR is generated, and NVIC manages it. The ISR handler
 * increments the ISR counter in 1.
 *
 * On the other side, the UART transmit the value of the counter,
 * and the status of the buttom:
 * - not pressed.
 * _ pressed.
 *
 * The Configuration for the UART is Baudrate 9600, 8N1.
 * There is a makefile to build.
 * make  clean
 * make bin/pio_periph.elf.bin
 * sudo make flash_pio_periph
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

std::uint32_t counter = 0;


extern "C" void __vector_pio_a_handler() __attribute__((used, noinline));
void __vector_pio_a_handler() //__attribute__((used, noinline))
{
  // Increment the 32-bit system tick with 0x80, representing 128 microseconds.


  // Read SW0 Interrupt Status
  volatile std::uint32_t sw0_interrupt_status;
  sw0_interrupt_status = mcal::reg::access< std::uint32_t,
                                            std::uint32_t,
                                            static_cast<std::uint32_t>(0x400E0E4C)>::reg_get();

  //Check the source pin that generated the interrupt.
  if ( sw0_interrupt_status & (0x1 << 2) )
    counter ++;
}


int main()
{
  mcal::init();

  //Enable the interrupt for the swhtich pin.
  mcal::irq::enableIRQ(mcal::reg:: pioa_periph_id);

  while (1)
    {
      //LED OFF
      mcal::port::yellow_led_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::seconds(1U));

      // LED ON
      mcal::port::yellow_led_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::seconds(1U));

      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send( counter + '0' );


      while(! mcal::port::sw0_button_pin.read_input_value() )
        {
          timer_type::blocking_delay(timer_type::milliseconds(100U));
          mcal::uart::the_uart.send( '_' );
        }

      timer_type::blocking_delay(timer_type::milliseconds(100U));
      mcal::uart::the_uart.send( '-' );

    }

  //Wait forever.
  return 0;
}
