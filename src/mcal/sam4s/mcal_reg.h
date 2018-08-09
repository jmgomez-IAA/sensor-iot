/**
 * @file mcal_reg.h
 * @brief SAM4S register memory map.
 * @description Defines the SAM4S registers memory map.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_REG_EMBEDDED_H_
  #define _MCAL_REG_EMBEDDED_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {

      // Bit-position values.
      constexpr std::uint8_t bval0  = 1U;
      constexpr std::uint8_t bval1  = 1U << 1U;
      constexpr std::uint8_t bval2  = 1U << 2U;
      constexpr std::uint8_t bval3  = 1U << 3U;
      constexpr std::uint8_t bval4  = 1U << 4U;
      constexpr std::uint8_t bval5  = 1U << 5U;
      constexpr std::uint8_t bval6  = 1U << 6U;
      constexpr std::uint8_t bval7  = 1U << 7U;

      // Global base addresses.
      // ==
      constexpr std::uint32_t periph_base     = UINT32_C(0x40000000);
      // System Control Space
      constexpr std::uint32_t scs_base        = UINT32_C(0xE000E000);

      constexpr std::uint32_t apb1periph_base = periph_base     + UINT32_C(0x00000000);
      constexpr std::uint32_t ahb1periph_base = periph_base     + UINT32_C(0x00020000);

      // Individual unit base addresses.
      // ==
      // System Control Block
      constexpr std::uint32_t scb_base        = scs_base        + UINT32_C(0x00000D00);
      constexpr std::uint32_t scb_vtor        = scs_base        + UINT32_C(0x00000D08);

      // Nested Vector Interrupt Controller
      constexpr std::uint32_t nvic_base       = scs_base        + UINT32_C(0x00000100);
      constexpr std::uint32_t nvic2_base      = scs_base        + UINT32_C(0x00000F00);

      // Power Management Controller
      constexpr std::uint32_t pmc_base        = periph_base     + UINT32_C(0x000E0400);

      constexpr std::uint32_t rcc_base        = ahb1periph_base + UINT32_C(0x00003800);
      constexpr std::uint32_t pwr_base        = apb1periph_base + UINT32_C(0x00007000);

      // Watchdog Control(* reg_wdt_mr) |=  WDT_WDDIS;
      constexpr std::uint32_t wdt_base        = periph_base     + UINT32_C(0x000E1450);

      // Parallel Input/Output Controller
      constexpr std::uint32_t pioa_base       = scs_base        + UINT32_C(0x0E00);
      constexpr std::uint32_t piob_base       = scs_base        + UINT32_C(0x1000);
      constexpr std::uint32_t pioc_base       = scs_base        + UINT32_C(0x2000);

      constexpr std::uint32_t flash_r_base    = ahb1periph_base + UINT32_C(0x00003C00);

      // Peripheral Memory Map Registers
      //Sys Timer.
      constexpr std::uint32_t syst_csr   = 0xE000E010U;
      constexpr std::uint32_t syst_rvr   = 0xE000E014U;
      constexpr std::uint32_t syst_cvr   = 0xE000E018U;
      constexpr std::uint32_t syst_calib = 0xE000E01CU;

      // Port Registers
      constexpr std::uint32_t gpio_base = 0x0;

      // Timer Registers
      constexpr std::uint32_t tim4_base = 0x0;

      // Watchdog Controller Registers
      constexpr std::uint32_t iwdg_ase = 0x0;

    }
  }
#endif // _MCAL_REG_EMBEDDED_H_
