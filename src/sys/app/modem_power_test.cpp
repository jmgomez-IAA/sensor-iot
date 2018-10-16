/**
 * @file modem_power_test.cpp
 * @brief Enable the Power Supply of the Modem 2G.
 * @description Configure the SoC pins that are
 * connected to the Modem, and tries to enable the
 * power.
 *
 * Pin PA15 should be an output (no pull-up). When it
 * is state low the modem is not powered and LED is
 * off. When the pin outputs a high, it feeds the
 * 2G modem with power.
 *
 * Pin PB14 should be an output (no pull-up). When it
 * outputs a high the modem boots. A delay between the
 * power on and the boot should be kept.
 *
 * return LED D19 should be green?
 *
 * There is a makefile to build.
 * make  clean
 * make modem_power
 *
 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>
#include <util/utility/util_time.h>

namespace{
  typedef util::timer<std::uint32_t> timer_type;


  mcal::port::port_pin<std::uint32_t,
                       std::uint32_t,
                       mcal::reg::pioa_base,
                       UINT32_C(19) > modem_power_enable_pin;


  mcal::port::port_pin<std::uint32_t,
                       std::uint32_t,
                       mcal::reg::piob_base,
                       UINT32_C(14) > bgs2_on_pin;

}

int main()
{
  mcal::init();

  //Enable the interrupt for the swicht pin.
  mcal::irq::enableIRQ(mcal::reg:: pioa_periph_id);

  modem_power_enable_pin.set_direction_output();
  modem_power_enable_pin.disable_pull_up();
  bgs2_on_pin.set_direction_output();
  bgs2_on_pin.disable_pull_up();

  modem_power_enable_pin.set_pin_low();
  bgs2_on_pin.set_pin_low();

  timer_type::blocking_delay(timer_type::seconds(1U));
  modem_power_enable_pin.set_pin_high();
  timer_type::blocking_delay(timer_type::seconds(1U));
  bgs2_on_pin.set_pin_high();

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
