/**
 * @file yellow_led_test.cpp
 * @brief Enables the yellow led of the board.
 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>

int main()
{

  mcal::init();

  //Toggle LED.
  led_yellow.toggle();

  //Wait forever.
  for(;;)
    {
      //      mcal::cpu::nop();
    }
}
