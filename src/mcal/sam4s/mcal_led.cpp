/**
 * @file mcal_led.cpp
 * @brief Implementation of microcontroller abstraction layer for port of SAM4S.
 * @description Instantiates an object of led_type which is the led, yellow present
 * on the board.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_led.h>

mcal::dev::led mcal::dev::led_yellow(mcal::reg::pioc_base, pioc_portpin_23);

mcal::dev::led::led(std::uint32_t puerto, std::uint32_t valor)
{
  port = puerto;
  bval = valor;

  //Writting 1 enables PIO to control this port pin.
  *reinterpret_cast<unsigned int *>(mcal::reg::pioc_per) |= bval;
  //Writting 1 set direction output.
  *reinterpret_cast<unsigned int *>(mcal::reg::pioc_oer) |= bval ;

  // Initilization to Low all pins??.
  *reinterpret_cast<unsigned int *>(mcal::reg::pioc_codr) = bval ; // on;
  led_is_on = true;
}


bool mcal::dev::led::switch_on(void)
{
  *reinterpret_cast<unsigned int *>(mcal::reg::pioc_codr) = bval ; // on;
  led_is_on = true;
  return led_is_on;
}

bool mcal::dev::led::switch_off(void)
{
  *reinterpret_cast<unsigned int *>(mcal::reg::pioc_sodr) = bval ; // on;
  led_is_on = false;
  return led_is_on;
}

void mcal::dev::led::toggle(void)
{

  //std::uint32_t led_port_pin_status = mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::pioc_odsr>::reg_get();
  //  if ((led_port_pin_status & bval) != 0)
  if (led_is_on)
  {
    *reinterpret_cast<unsigned int *>(mcal::reg::pioc_sodr) = bval ; // off;
    led_is_on = false;
  }
  else
    {
      *reinterpret_cast<unsigned int *>(mcal::reg::pioc_codr) = bval ; // on;
      led_is_on = true;
    }
}
