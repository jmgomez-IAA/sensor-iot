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

      // Peripheral Memory Map Registers
      //Sys Timer.
      constexpr std::uint8_t syst_csr   = 0xE000E010;
      constexpr std::uint8_t syst_rvr   = 0xE000E014;
      constexpr std::uint8_t syst_cvr   = 0xE000E018;
      constexpr std::uint8_t syst_calib = 0xE000E01C;

      //Parallel Input/Output Controller (PIO)

      constexpr std::uint32_t porta = 0x400E0E00U;
      constexpr std::uint32_t portb = 0x400E1000U;
      constexpr std::uint32_t portc = 0x400E1200U;

      constexpr std::uint32_t sfr_offset = 0;

      constexpr std::uint32_t pio_per = 0x0000U + sfr_offset;
      constexpr std::uint32_t pio_pdr = 0x0004U + sfr_offset;
      constexpr std::uint32_t pio_psr = 0x0008U + sfr_offset;
      constexpr std::uint32_t pio_reserved1 = 0x000CU + sfr_offset;

      constexpr std::uint32_t pio_oer = 0x0010U + sfr_offset;
      constexpr std::uint32_t pio_odr = 0x0014U + sfr_offset;
      constexpr std::uint32_t pio_osr = 0x0018U + sfr_offset;
      constexpr std::uint32_t pio_reserved2 = 0x001CU + sfr_offset;

      constexpr std::uint32_t pio_ifer = 0x0020U + sfr_offset;
      constexpr std::uint32_t pio_ifdr = 0x0024U + sfr_offset;
      constexpr std::uint32_t pio_ifsr = 0x0028U + sfr_offset;
      constexpr std::uint32_t pio_reserved3 = 0x002CU + sfr_offset;

      constexpr std::uint32_t pio_sodr = 0x0030U + sfr_offset;
      constexpr std::uint32_t pio_codr = 0x0034U + sfr_offset;
      constexpr std::uint32_t pio_odsr = 0x0038U + sfr_offset;
      constexpr std::uint32_t pio_pdsr = 0x003CU + sfr_offset;

      constexpr std::uint32_t pio_ier = 0x0040U + sfr_offset;
      constexpr std::uint32_t pio_idr = 0x0044U + sfr_offset;
      constexpr std::uint32_t pio_imr = 0x0048U + sfr_offset;
      constexpr std::uint32_t pio_isr = 0x004CU + sfr_offset;

      constexpr std::uint32_t pio_mder = 0x0050U + sfr_offset;
      constexpr std::uint32_t pio_mddr = 0x0054U + sfr_offset;
      constexpr std::uint32_t pio_mdsr = 0x0058U + sfr_offset;
      constexpr std::uint32_t pio_reserved4 = 0x005CU + sfr_offset;

      constexpr std::uint32_t pio_pudr = 0x0060U + sfr_offset;
      constexpr std::uint32_t pio_puer = 0x0064U + sfr_offset;
      constexpr std::uint32_t pio_pusr = 0x0068U + sfr_offset;
      constexpr std::uint32_t pio_reserved5 = 0x006CU + sfr_offset;

      constexpr std::uint32_t pio_abcdsr1 = 0x0070U + sfr_offset;
      constexpr std::uint32_t pio_abcdsr2 = 0x0074U + sfr_offset;
      constexpr std::uint32_t pio_reserved6 = 0x0078U + sfr_offset;
      constexpr std::uint32_t pio_reserved7 = 0x007CU + sfr_offset;

      constexpr std::uint32_t pio_ifscdr = 0x0080U + sfr_offset;
      constexpr std::uint32_t pio_ifscer = 0x0084U + sfr_offset;
      constexpr std::uint32_t pio_ifscsr = 0x0088U + sfr_offset;
      constexpr std::uint32_t pio_scdr = 0x008CU + sfr_offset;

      constexpr std::uint32_t pio_ppddr = 0x0090U + sfr_offset;
      constexpr std::uint32_t pio_ppder = 0x0094U + sfr_offset;
      constexpr std::uint32_t pio_ppdsr = 0x0098U + sfr_offset;
      constexpr std::uint32_t pio_reserved8 = 0x09CU + sfr_offset;

      constexpr std::uint32_t pio_ower = 0x00A0U + sfr_offset;
      constexpr std::uint32_t pio_owdr = 0x00A4U + sfr_offset;
      constexpr std::uint32_t pio_owsr = 0x00A8U + sfr_offset;
      constexpr std::uint32_t pio_reserved9 = 0x00ACU + sfr_offset;

      constexpr std::uint32_t pio_aimer = 0x00B0U + sfr_offset;
      constexpr std::uint32_t pio_aimdr = 0x00B4U + sfr_offset;
      constexpr std::uint32_t pio_aimmr = 0x00B8U + sfr_offset;
      constexpr std::uint32_t pio_reserved10 = 0x00BCU + sfr_offset;

      constexpr std::uint32_t pio_esr = 0x00C0U + sfr_offset;
      constexpr std::uint32_t pio_lsr = 0x00C4U + sfr_offset;
      constexpr std::uint32_t pio_elsr = 0x00C8U + sfr_offset;
      constexpr std::uint32_t pio_reserved11 = 0x00CCU + sfr_offset;

      constexpr std::uint32_t pio_fellsr = 0x00D0U + sfr_offset;
      constexpr std::uint32_t pio_rehlsr = 0x00D4U + sfr_offset;
      constexpr std::uint32_t pio_frlhsr = 0x00D8U + sfr_offset;
      constexpr std::uint32_t pio_reserved = 0x00DCU + sfr_offset;

      constexpr std::uint32_t pio_locksr = 0x00E0U + sfr_offset;
      constexpr std::uint32_t pio_wpmr = 0x00E4U + sfr_offset;
      constexpr std::uint32_t pio_wpsr = 0x00E8U + sfr_offset;
      constexpr std::uint32_t pio_reserved = 0x00ECU + sfr_offset;

      constexpr std::uint32_t pio_schmitt = 0x0100U + sfr_offset;

      constexpr std::uint32_t pio_pcmr = 0x0150U + sfr_offset;
      constexpr std::uint32_t pio_pcier = 0x0154U + sfr_offset;
      constexpr std::uint32_t pio_pcidr = 0x0158U + sfr_offset;
      constexpr std::uint32_t pio_pcimr = 0x015CU + sfr_offset;
      constexpr std::uint32_t pio_pcisr = 0x0160U + sfr_offset;
      constexpr std::uint32_t pio_pcrhr = 0x0164U + sfr_offset;

    }
  }
#endif // _MCAL_REG_EMBEDDED_H_
