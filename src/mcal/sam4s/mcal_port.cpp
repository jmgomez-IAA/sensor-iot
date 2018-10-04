///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg_access.h>

// Yellow LED on port pin PIOC_23
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioc_base,
                     UINT32_C(23) > mcal::port::yellow_led_pin;


mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(2) > sw0_button_pin;

// UART1 TX on port pin PIOB_3
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::piob_base,
                     UINT32_C(3) > mcal::port::aurt1_tx_pin;

// TWI0 Data and CLK pins, which are connected to PIOA, should be multiplexed
// in order to be managed with peripheral A.
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(4) > mcal::port::twi0_clock_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(3) > mcal::port::twi0_data_pin;

/*
// TWI1 Data and CLK pins, which are connected to PIOB, should be multiplexed
// in order to be managed with peripheral A.
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::piob_base,
                     UINT32_C(5) > mcal::port::twi1_clock_pin;

mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::piob_base,
                     UINT32_C(4) > mcal::port::twi1_data_pin;
*/

void mcal::port::init(const config_type*)
{
  //Enable Periph PIOA on  PMC
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 11))>::reg_or();

  //Enable Periph PIOB on  PMC
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 12))>::reg_or();

  //Enable Periph PIOC on  PMC
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    static_cast<std::uint32_t>(UINT32_C(0x1 << 13))>::reg_or();


  yellow_led_pin.set_direction_output();

  sw0_button_pin.set_direction_input();

  //Este clear deberia ir en el enable de la interrupcion, no aqui.
  //Clear interrupt pending status.
  volatile std::uint32_t sw0_interrupt_status;
  sw0_interrupt_status = mcal::reg::access< std::uint32_t,
                                            std::uint32_t,
                                            static_cast<std::uint32_t>(0x400E0E4C)>::reg_get();

  sw0_button_pin.enable_interrupt_edge();
}
