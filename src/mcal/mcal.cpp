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
  //  mcal::cpu::init(nullptr);
  //mcal::irq::init(nullptr);
  //mcal::led::init(nullptr);
  
  mcal::fd::init( nullptr );
}
