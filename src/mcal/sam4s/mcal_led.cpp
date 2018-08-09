/**
 * @file mcal_led.cpp
 * @brief Implementation of microcontroller abstraction layer for port of SAM4S.
 * @description Instantiates an object of led_type which is the led, yellow present
 * on the board.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_led.h>
#include <mcal_reg_access.h>


namespace mcal
{
  namespace led
  {

    const led led_yellow(mcal::reg::pioc_base, 0x800000U);

  }
}
