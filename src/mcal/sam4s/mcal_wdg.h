/**
 * @file mcal_wdg.h
 * @brief Microcontroller abstraction layer for SAM4S ARM Cortex M CPU
 * @description Inicialization and definitions for the Watchdog CPU ARM Cortex M4
 * abstraction layer for the microcontroller SAM4S.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */


#ifndef _MCAL_WDG_SAM4S_EMBEDDED_2018_
#define _MCAL_WDG_SAM4S_EMBEDDED_2018_


namespace mcal
{
  namespace wdg
  {
    typedef void config_type;
    void init(const config_type*);
    void enable(const config_type*);
    void disable(const config_type*)
    {
      // Disable the Watchdog
      (* reg_wdt_mr) |=  WDT_WDDIS;
    };
  }
}

#endif  //_MCAL_WDG_SAM4S_EMBEDDED_2018
