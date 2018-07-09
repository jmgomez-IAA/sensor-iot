/**
 * @file mcal_port.h
 * @brief Microcontroller abstraction layer for PIO of SAM4S.
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_PORT_SAM4S_EMBEDDED_2018_
#define _MCAL_PORT_SAM4S_EMBEDDED_2018_

#include <mcal_reg_access.h>

namespace mcal
{
  namespace port
  {

    typedef void config_type;
    void init(const config_type *);

    //Configurar un puerto:
    // REG_PIOA_PER |= PIO_PER_P11; //enable PIO controller on PA11
    //REG_PIOB_PDR |= PIO_PER_P3; //disable PIO controller on PB3

    //REG_PIOA_ODR |= PIO_PER_P11; //disable output on pin PA11

    template<typename addr_type,
             typename reg_type,
             const addr_type port,
             const reg_type bpos>
    class port_pin
    {
    public:
      static void set_direction_output()
      {
        // Set the port pin's direction to output.
        mcal::reg::access<addr_type, reg_type, pdir, bpos>::bit_set();
        //REG_PIOA_OER |= PIO_PER_P11; //enable output on pin PA11
      }

      static void set_direction_input()
      {
        // Set the port pin's direction to input.
        mcal::reg::access<addr_type, reg_type, pdir, bpos>::bit_clr();
      }

      static void set_pin_high()
      {
        // Set the port output value to high.
        mcal::reg::access<addr_type, reg_type, port, bpos>::bit_set();
        //REG_PIOA_SODR |= PIO_PER_P11; //set output high on pin PA11
      }

      static void set_pin_low()
      {
        // Set the port output value to low.
        mcal::reg::access<addr_type, reg_type, port, bpos>::bit_clr();
        //REG_PIOA_CODR |= PIO_PER_P11; //set output low on pin PA11
      }

      static bool read_input_value()
      {
        // Read the port input value.
        return mcal::reg::access<addr_type, reg_type, pinp, bpos>::bit_get();
        //return PIO_PSR_P3; //disable PIO controller on PB3
      }

      static void toggle_pin()
      {
        // Toggle the port output value.
        mcal::reg::access<addr_type, reg_type, port, bpos>::bit_not();
      }

    private:
      static constexpr addr_type pdir = port - 1U;
      static constexpr addr_type pinp = port - 2U;
    };

  }

}

#endif  //_MCAL_PORT_SAM4S_EMBEDDED_2018
