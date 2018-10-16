/**
 * @file eefc_periph_test.cpp
 * @brief Manages the EEFC Controller of the SAM4S processor.
 * @description Modifies a value stored in the Flash and verifies
 * the value is already there after reset.
 *
 * make  clean
 * make  eefc_periph
 *
 * @author Juan Manuel Gómez López <jmgomez@iaa.es>
 * @copyright
 *
 **/

#include <mcal/mcal.h>
#include <util/utility/util_time.h>

namespace{
  typedef util::timer<std::uint32_t> timer_type;
}

int main()
{

  constexpr std::uint32_t pattern = 0xABCDEF00;

  volatile std::uint32_t *eefc_fmr= reinterpret_cast<std::uint32_t*>(0x400E0A00);
  volatile std::uint32_t *eefc_fcr= reinterpret_cast<std::uint32_t*>(0x400E0A04);
  volatile std::uint32_t *eefc_fsr= reinterpret_cast<std::uint32_t*>(0x400E0A08);
  volatile std::uint32_t *eefc_frr= reinterpret_cast<std::uint32_t*>(0x400E0A0C);

  std::uint32_t get_descriptor_cmd = 0x0;
  std::uint32_t write_page_cmd = 0x1;

  std::uint32_t flash_cmd_key = (0x5A << 24);
  volatile std::uint32_t *page_buffer= reinterpret_cast<std::uint32_t*>(0x00410000);
  std::uint32_t page_number = 128 << 8; // (0x82 << 8);


  /**
   * Latch Buffer is the buffer, it is only accesign the addresses
   */
  volatile std::uint32_t *latch_buffer_start= page_buffer;

  for (std::uint32_t i=0; i < 0x80; ++i)
    {
      (*latch_buffer_start) = pattern | i;
      latch_buffer_start++;
    }

  //Send the Write Command.
  (*eefc_fcr) = (flash_cmd_key | page_number | write_page_cmd );

  //Wait for the operation to be executed.
  timer_type::blocking_delay(timer_type::seconds(1U));


  if ((*eefc_fsr) & 0x1)
    {
      //LED ON: Success
      mcal::port::led2_pin.set_pin_low();
      timer_type::blocking_delay(timer_type::seconds(1U));
    }
  else
    {
      // LED OFF
      mcal::port::led2_pin.set_pin_high();
      timer_type::blocking_delay(timer_type::seconds(1U));
    }


  //Wait forever.
  return 0;
}
