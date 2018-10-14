///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg_access.h>

// Yellow LED on port pin PIOA_14  D13
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(14) > mcal::port::led1_pin;

// Yellow LED on port pin PIOA_15
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(15) > mcal::port::led2_pin;

// Pull-down must be enabled . Estan al reves. Este PA26 es SW3
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(26) > mcal::port::sw3_button_pin;

// Pull-down must be enabled PA13 es sW2.
mcal::port::port_pin<std::uint32_t,
                     std::uint32_t,
                     mcal::reg::pioa_base,
                     UINT32_C(13) >  mcal::port::sw2_button_pin;

// Address bits
mcal::port::port_pin<std::uint32_t, std::uint32_t, mcal::reg::pioa_base, UINT32_C(0)  >  mcal::port::addr0_pin;
mcal::port::port_pin<std::uint32_t, std::uint32_t, mcal::reg::pioa_base, UINT32_C(1)  >  mcal::port::addr1_pin;
mcal::port::port_pin<std::uint32_t, std::uint32_t, mcal::reg::pioa_base, UINT32_C(2)  >  mcal::port::addr2_pin;
mcal::port::port_pin<std::uint32_t, std::uint32_t, mcal::reg::pioa_base, UINT32_C(30) >  mcal::port::addr3_pin;
mcal::port::port_pin<std::uint32_t, std::uint32_t, mcal::reg::pioa_base, UINT32_C(28) >  mcal::port::addr4_pin;
mcal::port::port_pin<std::uint32_t, std::uint32_t, mcal::reg::pioa_base, UINT32_C(27) >  mcal::port::addr5_pin;
mcal::port::port_pin<std::uint32_t, std::uint32_t, mcal::reg::pioa_base, UINT32_C(11) >  mcal::port::addr6_pin;
mcal::port::port_pin<std::uint32_t, std::uint32_t, mcal::reg::pioa_base, UINT32_C(12) >  mcal::port::addr7_pin;

/*
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
*/
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


  led1_pin.set_direction_output();
  led2_pin.set_direction_output();

  //
  sw2_button_pin.set_direction_input();
  sw2_button_pin.enable_pull_down();

  //
  sw3_button_pin.set_direction_input();
  sw3_button_pin.enable_pull_down();

  //Este clear deberia ir en el enable de la interrupcion, no aqui.
  //Clear interrupt pending status.

  volatile std::uint32_t sw2_interrupt_status;
  sw2_interrupt_status = mcal::reg::access< std::uint32_t,
                                            std::uint32_t,
                                            static_cast<std::uint32_t>(0x400E0E4C)>::reg_get();

  //  mcal::irq::enableIRQ(mcal::reg:: pioa_periph_id);
  sw2_button_pin.enable_interrupt_edge();

  //
  addr0_pin.enable_pull_down();
  addr0_pin.set_direction_input();
  addr1_pin.enable_pull_down();
  addr1_pin.set_direction_input();
  addr2_pin.enable_pull_down();
  addr2_pin.set_direction_input();
  addr3_pin.enable_pull_down();
  addr3_pin.set_direction_input();
  addr4_pin.enable_pull_down();
  addr4_pin.set_direction_input();
  addr5_pin.enable_pull_down();
  addr5_pin.set_direction_input();
  addr6_pin.enable_pull_down();
  addr6_pin.set_direction_input();
  addr7_pin.enable_pull_down();
  addr7_pin.set_direction_input();

}

std::uint32_t mcal::port::counter;
/**
 * Interrupt handler for the PIO A Controller
 */
extern "C" void __vector_pio_a_handler() __attribute__((used, noinline));
void __vector_pio_a_handler() //__attribute__((used, noinline))
{

  // Read SW2 Interrupt Status
  volatile std::uint32_t sw2_interrupt_status;
  sw2_interrupt_status = mcal::reg::access< std::uint32_t,
                                            std::uint32_t,
                                            static_cast<std::uint32_t>(0x400E0E4C)>::reg_get();

  //Check the source pin that generated the interrupt.
  if ( sw2_interrupt_status & (0x1 << 13) )
    mcal::port::counter ++;
}
