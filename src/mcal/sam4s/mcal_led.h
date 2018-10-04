/**
 * @file mcal_led.h
 * @brief Microcontroller abstraction layer for the LED on PC4 SAM4S.
 * @description Inicialization and definitions for the LED on PC4 pin
 * of the SAM4S board.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_LED_SAM4S_EMBEDDED_2018_
#define _MCAL_LED_SAM4S_EMBEDDED_2018_

#include <cstdint>
//#include <iostream>
#include <mcal_reg_access.h>
#include <mcal_reg.h>

namespace mcal
{
  namespace dev
  {
    typedef void config_type;

    void init(config_type*);

    constexpr std::uint32_t pioc_portpin_23 =  (1<<23);

    class led
    {
    public:
      typedef std::uint32_t port_type;
      typedef std::uint32_t bval_type;
      //Conf registers and address are 32bit.
      /**
       * @brief bval es el valor de pin a poner a 1,, bval=2 => pin 1 del puerto.
       **/
      led(std::uint32_t puerto, std::uint32_t valor);
      bool switch_on(void);
      bool switch_off(void);
      void toggle(void);

    private:
      std::uint32_t port;
      std::uint32_t bval;
      bool led_is_on;
    };

    extern led led_yellow;

  }

}

#endif  //_MCAL_LED_SAM4S_EMBEDDED_2018
