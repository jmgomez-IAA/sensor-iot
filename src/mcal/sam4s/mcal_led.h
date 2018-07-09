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

namespace mcal
{
  namespace led
  {

    template<typename addr_type,
             typename reg_type,
             const addr_type port,
             const reg_type bpos>
    class led
    {
    public:
      typedef std::uint8_t port_type;
      typedef std::uint8_t bval_type;
      led()
      {
        //Set the pin value low.
        port_pin_type::set_pin_low();

        //Set the pin direction out
        port_pin_type::set_direction_output();
      }

      toggle()
      {
        port_pin_type::toggle_pin();
      }

    private:
      typedef mcal::port::port_pin<addr_type,
                                   reg_type,
                                   port,
                                   bpos> port_pin_type;
    };

    //The led is in the PIO Controller C, at pin 4.
  typedef led<std::uint32_t,
              std::uint32_t,
              mcal::reg::portc,
              0x4> led_type;

  extern const led_type led_yellow;

  }

}

#endif  //_MCAL_LED_SAM4S_EMBEDDED_2018
