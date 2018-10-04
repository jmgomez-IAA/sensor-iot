/**
 * @file mcal_irq.cpp
 * @brief
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_cpu.h>
#include <mcal_reg_access.h>

//#include <mcal_osc.h>
//#include <mcal_port.h>
//#include <mcal_wdg.h>

void mcal::cpu::init()
{

  //Disable Interrupts
  /*
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_cr,
                    UINT32_C(0x24003010)>::reg_set();
  */
  //Configure the clock?? pllcfgr rcc clock fpu.

  //Set the vector table address
  constexpr std::uint32_t vtor_base_addr = UINT32_C(0x00400000);
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::scb_vtor,
                    vtor_base_addr>::reg_set();

  //Enable PMC
  // Esto debemos moverlo a mcal_port.cpp
  /*
  constexpr std::uint32_t pmc_pioc_enable = UINT32_C(1 << 13);
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    pmc_pioc_enable>::reg_or();
  */
  /*
  constexpr std::uint32_t pmc_pioa_enable = UINT32_C(1 << 11);
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    pmc_pioa_enable>::reg_or();
*/
  /*
  constexpr std::uint32_t pmc_piob_enable = UINT32_C(1 << 12);
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    pmc_piob_enable>::reg_or();

  */
  /*
  constexpr std::uint32_t piob_disable_uart_pin = UINT32_C(1 << 3);
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::piob_pdr,
                    piob_disable_uart_pin>::reg_or();
*/
  /*
  //Enable UART1
  constexpr std::uint32_t pmc_uart1_enable = UINT32_C(1 << 9);
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::pmc_pcer0,
                    pmc_uart1_enable>::reg_or();
  */
  //  (* pcm_pioc_enable)  |= (1 << PCM_PIOC_ID);


  // mcal::wdg::init(nullptr);
  //mcal::port::init(nullptr);
  //mcal::osc::init(nullptr);

}
