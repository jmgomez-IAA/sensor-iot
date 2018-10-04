/**
 * @file software_interrupt_test.cpp
 * @brief Enables the interrups of the NVIC and checks its handlers.
 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>

// System clock definitions
#define BOARD_FREQ_STARTUP_US 15625UL
#define BOARD_FREQ_SLCK_XTAL 32768UL
#define BOARD_FREQ_MAINCK_XTAL 12000000UL

// PMC Controller definitions
//#define OSC_MAINCK_4M_RX_HZ
//#define SYSCLK_SRC_MAINCK_4M_RC 3 // Internal 4 MHz RC oscillator Master CLK source

bool isr_handled = false;
std::uint32_t counter = 0;
constexpr std::uint32_t system_tick_100ms_reload = 0x000F8FFFUL;

extern "C" void  __sys_tick_handler() __attribute__((used, noinline));
void __sys_tick_handler() //__attribute__((used, noinline))
{
  // Increment the 32-bit system tick with 0x80, representing 128 microseconds.
  counter += 10;
}


int main()
{

  constexpr std::uint32_t nvic_stir_addr = 0xE000EF00UL;
  std::uint32_t * nvic_stir = reinterpret_cast<std::uint32_t *> ( nvic_stir_addr);

  mcal::wdt::disable();
  mcal::irq::enable(nullptr);

  //  constexpr std::uint32_t pioc_portpin_23 =  (1<<23);
  mcal::port::port_pin<std::uint32_t,
                       std::uint32_t,
                       0x400E1200,
                       UINT32_C(23) > yellow_led_pin;

  yellow_led_pin.set_direction_output();


  // Set the timer reload value
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::syst_rvr, 0x000F8FFF>::reg_set();

  // Reset the current value
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::syst_cvr, 0x00000000>::reg_set();

  // Set the system timer clock source to Main Clk and  f_osc/8 = 2MHz and begin counting.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::syst_csr, 0x00000007>::reg_set();


  //Each time an interrupt is detected the led, blinks.
  while (1)
    {

      isr_handled = (counter >= 10);
      if( isr_handled ){
        yellow_led_pin.set_pin_high();
        // 400ms delay.
        for (int i = 0; i< 4000; ++i)
          for (int j = 0; j< 100; ++j)
            mcal::cpu::nop();

        /*
        for (int i = 0; i< 4000; ++i)
          for (int j = 0; j< 100; ++j)
            mcal::cpu::nop();
*/
        counter = 0;
        isr_handled = false;
      }

      // Verification
      yellow_led_pin.set_pin_low();
      /*      for (int i = 0; i< 4000; ++i)
        for (int j = 0; j< 100; ++j)
          mcal::cpu::nop();
      */
      // isr_handler = true;
      //      (*nvic_stir) = 15;

    }

  //Wait forever.
  return 0;
}
