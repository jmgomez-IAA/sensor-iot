/**
 * @file mcal.h
 * @brief Microcontroller abstraction layer
 * @description Include the initialization and hardware
 * abstraction for the microcontroller.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_EMBEDDED_2018_
#define _MCAL_EMBEDDED_2018_

#include <mcal_cpu.h>
#include <mcal_wdt.h>
#include <mcal_gpt.h>
#include <mcal_irq.h>
//#include <mcal_led.h>
#include <mcal_port.h>
#include <mcal_uart.h>
#include <mcal_i2c.h>

namespace mcal
{
  void init();
}

#endif //_MCAL_EMBEDDED_2018_
