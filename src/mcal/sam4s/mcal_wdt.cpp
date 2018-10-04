/**
 * @file mcal_wdt.cpp
 * @brief
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_wdt.h>
#include <mcal_reg_access.h>

//#include <mcal_osc.h>
//#include <mcal_port.h>

void mcal::wdt::init(const config_type*){}
void mcal::wdt::enable(const config_type*){}

void mcal::wdt::disable()
{

  //Disable the Watchdog
  constexpr std::uint32_t wdt_wddis = UINT32_C(0x00008000);
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt_mr,
                    wdt_wddis>::reg_set();
}
