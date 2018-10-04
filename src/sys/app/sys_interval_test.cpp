/**
 * @file sys_tick_chrono_test.cpp
 * @brief Enables the interrups of the sys_tick, and
 * manages it from chrono class.
 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>
#include <util/utility/util_time.h>

// System clock definitions
#define BOARD_FREQ_STARTUP_US 15625UL
#define BOARD_FREQ_SLCK_XTAL 32768UL
#define BOARD_FREQ_MAINCK_XTAL 12000000UL

// PMC Controller definitions
//#define OSC_MAINCK_4M_RX_HZ
//#define SYSCLK_SRC_MAINCK_4M_RC 3 // Internal 4 MHz RC oscillator Master CLK source


namespace{
  typedef util::timer<std::uint32_t> timer_type;
  timer_type app_timer(timer_type::seconds(1U));
}


int main()
{

  //constexpr std::uint32_t nvic_stir_addr = 0xE000EF00UL;
  //  std::uint32_t * nvic_stir = reinterpret_cast<std::uint32_t *> ( nvic_stir_addr);
  mcal::init();
  //  constexpr std::uint32_t pioc_portpin_23 =  (1<<23);
  mcal::port::port_pin<std::uint32_t,
                       std::uint32_t,
                       0x400E1200,
                       UINT32_C(23) > yellow_led_pin;

  yellow_led_pin.set_direction_output();


  //Blinks with chrono::interval();
  bool new_interval = true;
  bool led_on = true;
  while (1)
    {
      // LED Off.
      if ( app_timer.timeout())
        {
          app_timer.start_interval(timer_type::seconds(2U));
          led_on = !led_on;
        }

      if (led_on)
        yellow_led_pin.set_pin_high();
      else
        yellow_led_pin.set_pin_low();
    }

  //Wait forever.
  return 0;
}
