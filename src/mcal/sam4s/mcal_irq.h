/**
 * @file mcal_irq.h
 * @brief Microcontroller abstraction layer for SAM4S ARM Cortex M CPU
 * @description Inicialization and definitions for the CPU ARM Cortex M4
 * abstraction layer for the microcontroller SAM4S.
 * Section 12.8 (pag 196) : Nested vector interrupt controller
 * Up to 35 interrupts.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

//Links: https://arobenko.gitbooks.io/bare_metal_cpp/content/peripherals/
#ifndef _MCAL_IRQ_SAM4S_EMBEDDED_2018_
#define _MCAL_IRQ_SAM4S_EMBEDDED_2018_

#include <mcal/mcal.h>

namespace mcal
{
  namespace irq
  {

    typedef void config_type;

    /**
     *
     **/
    void init(const config_type*);

    /**
     * @ brief Enable the interrupts.
     **/
    void enable(const config_type*);

    /**
     * @brief Disable the interrupts
     **/
    void disable(const config_type*);

  }
}

#endif  //_MCAL_IRQ_SAM4S_EMBEDDED_2018
