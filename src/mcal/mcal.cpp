/**
 * @file mcal.cpp
 * @brief Microcontroller abstraction layer
 * @description Include the initialization and hardware
 * abstraction for the microcontroller.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include <mcal/mcal.h>

void mcal::init()
{

  mcal::cpu::init();

  mcal::wdt::disable();

  //Required to use sys_tick_isr
  mcal::irq::init(nullptr);

  mcal::gpt::init(nullptr);
  mcal::port::init(nullptr);
  //  mcal::uart::init(nullptr);
  //  mcal::i2c::init(nullptr);


  //mcal::led::init(nullptr);
}
