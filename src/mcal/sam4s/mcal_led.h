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

namespace mcal
{
  namespace led
  {
    typedef void config_type;
    void init(config_type*);

    class led
    {
    public:
      //Conf registers and address are 32bit.
      typedef std::uint32_t port_type;
      typedef std::uint32_t bval_type;

      /**
       * @brief bval es el valor de pin a poner a 1,, bval=2 => pin 1 del puerto.
       **/
      led(const port_type p,
          const bval_type b) : port(p),
                               bval(b)
      {

        *reinterpret_cast<volatile bval_type*>(0x400E0410) |= static_cast<bval_type>(1<<13);

        //Enable the port pin to manage with PIO (pio_per).
        *reinterpret_cast<volatile bval_type*>(port)  |= static_cast<bval_type>(bval);
        // Set the port pin to low.
        //*reinterpret_cast<volatile bval_type*>(port+ 0x34U) |= static_cast<bval_type>(bval);

        // Set the port pin to output.
        *reinterpret_cast<volatile bval_type*>(port + 0x10U) |= bval;
      }

      void toggle(void) const
      {

        // Set the port pin to low.
        *reinterpret_cast<volatile bval_type*>(port+ 0x34U) |= static_cast<bval_type>(bval);

        // Toggle the LED.
        //*reinterpret_cast<volatile bval_type*>(port+0x30U) |= bval;
      }

    private:
      const port_type port;
      const bval_type bval;
    };

    extern const led led_yellow;

  }

}

#endif  //_MCAL_LED_SAM4S_EMBEDDED_2018
