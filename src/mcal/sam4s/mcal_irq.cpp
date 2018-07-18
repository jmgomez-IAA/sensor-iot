/**
 * @file mcal_irq.cpp
 * @brief
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_irq.h>

inline void mcal::irq::enable(const config_type*)
{
  __asm volatile("cpsie i");
}

inline void mcal::irq::disable(const config_type*)
{
  __asm volatile("cpsid i");
}

/*
void dummy_handler(const config_type*)
{
  while(1){
    mcal::cpu::nop();
  }
}
*/
