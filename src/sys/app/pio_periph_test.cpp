/**
 * @file pio_periph_test.cpp
 * @brief Manages the PIO Controller of the SAM4S processor.
 * @description Implement the unit test case, pio_periph,
 * which blinks the LED D13 with a 1 second frequency and
 * reads the value of the switch SW3. While  it is presed,
 * the test blinks the LED D14 with a 1 second frequency.
 * When the Switch button SW2 (PA) is pressed/released
 * the an ISR is generated, and NVIC manages it. The ISR handler
 * increments the ISR counter in 1.
 * When the counter, reaches 10 (5 time pressed) the leds remain
 * enabled forever.
 *
 * There is a makefile to build.
 * make  clean
 * make pio_periph
 *
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

  //Enable the interrupt for the swicht pin.
  mcal::irq::enableIRQ(mcal::reg:: pioa_periph_id);

  while (1)
    {
      //LED OFF
      mcal::port::led1_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::seconds(1U));
      // LED ON

      mcal::port::led1_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::seconds(1U));
      //      mcal::uart::the_uart.send( counter + '0' );


      while( mcal::port::sw3_button_pin.read_input_value() )
        {
          mcal::port::led2_pin.set_pin_high();
          timer_type::blocking_delay(timer_type::seconds(1U));
          //          mcal::uart::the_uart.send( '_' );
          // LED ON
          mcal::port::led2_pin.set_pin_low();
          timer_type::blocking_delay(timer_type::seconds(1U));
        }

      //      timer_type::blocking_delay(timer_type::milliseconds(100U));
      //      mcal::uart::the_uart.send( '-' );

      while(mcal::port::counter > 10)
        {
        mcal::port::led2_pin.set_pin_low();
        mcal::port::led1_pin.set_pin_low();
        }
    }

  //Wait forever.
  return 0;
}
