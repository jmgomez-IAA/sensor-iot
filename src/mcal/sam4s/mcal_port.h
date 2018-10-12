/**
 * @file mcal_port.h
 * @brief Port pin abstraction layer.
 * @description Manages de port pins of the sam4s
 */

#ifndef MCAL_PORT_2018_01_10_H_
  #define MCAL_PORT_2018_01_10_H_

  #include <mcal_reg_access.h>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;
      void init(const config_type*);

      template<typename addr_type,
               typename reg_type,
               const addr_type port,
               const reg_type bpos>
      class port_pin
      {
      public:

        static void periphA_manage_pin()
        {
          // Disable the pin for PIO_Controller. Allows, periph to manage it.
          mcal::reg::access<std::uint32_t,
                            std::uint32_t,
                            port_disable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();

          // Set the peripheral A to manage the pin. (00)
          mcal::reg::access<std::uint32_t,
                            std::uint32_t,
                            peripheral_select_register,
                            ~static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_and();

          mcal::reg::access<std::uint32_t,
                            std::uint32_t,
                            peripheral_select_register+0x4,
                            ~static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_and();

          /*
          // Set for no pull up, no pull down.
          mcal::reg::access<addr_type,
                            reg_type,
                            pull_up_pull_down_register,
                            ~static_cast<std::uint32_t>(UINT32_C(0x03) << (bpos * 2U))>::reg_and();
          */
        }

        static void set_direction_output()
        {
          // Set the port pin control bits.

          // Set for no pull up, no pull down.
          /*         mcal::reg::access<addr_type,
                            reg_type,
                            pull_up_pull_down_register,
                            ~static_cast<std::uint32_t>(UINT32_C(0x03) << (bpos * 2U))>::reg_and();

          // Select the fastest output speed.
          mcal::reg::access<addr_type,
                            reg_type,
                            output_speed_register,
                            static_cast<std::uint32_t>(UINT32_C(0x03) << (bpos * 2U))>::reg_or();

          // Set the port pin to push-pull output type.
          mcal::reg::access<addr_type,
                            reg_type,
                            output_type_register,
                            bpos>::bit_clr();
          */
          // Set the port pin direction to digital output.
          mcal::reg::access<addr_type,
                            reg_type,
                            port_enable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();

          mcal::reg::access<addr_type,
                            reg_type,
                            output_enable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();

          mcal::reg::access<addr_type,
                            reg_type,
                            clear_output_data,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();
        }

        static void set_direction_input()
        {

          //Enable the pin to be managed by PIO Controller
          mcal::reg::access<addr_type,
                            reg_type,
                            port_enable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();

          // Set the port pin direction to digital input.
          /*          mcal::reg::access<addr_type,
                            reg_type,
                            output_enable_register,
                            ~static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_and();*/
          // Disable Output
          mcal::reg::access<addr_type,
                            reg_type,
                            output_disable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();

          // Disable Pull-up
          /*          mcal::reg::access<addr_type,
                            reg_type,
                            pull_up_disable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();
          */
          mcal::reg::access<addr_type,
                            reg_type,
                            glicth_filter_disable,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();

          mcal::reg::access<addr_type,
                            reg_type,
                            clear_output_data,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();

          mcal::reg::access<addr_type,
                            reg_type,
                            interrupt_disable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();
        }

        static void enable_pull_down()
        {
          mcal::reg::access<addr_type,
                            reg_type,
                            pull_down_enable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();
        }

        static void disable_pull_down()
        {
          mcal::reg::access<addr_type,
                            reg_type,
                            pull_down_disable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();
        }


        static void enable_pull_up()
        {
          mcal::reg::access<addr_type,
                            reg_type,
                            pull_up_enable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();
        }

        static void disable_pull_up()
        {
          mcal::reg::access<addr_type,
                            reg_type,
                            pull_up_disable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();
        }

        static void enable_interrupt_edge()
        {
          mcal::reg::access<addr_type,
                            reg_type,
                            interrupt_disable_register,
                            ~static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_and();

          //Enable Interrupts for pin
          mcal::reg::access<addr_type,
                            reg_type,
                            interrupt_enable_register,
                            static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos))>::reg_or();

          // Set the port output value to high.
          /*          mcal::reg::access<addr_type,
                            reg_type,
                            set_output_data,
                            bpos>::bit_set();*/
        }


        static void set_pin_high()
        {
          // Set the port output value to high.
          mcal::reg::access<addr_type,
                            reg_type,
                            set_output_data,
                            bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Set the port output value to low.
          mcal::reg::access<addr_type,
                            reg_type,
                            clear_output_data,
                            bpos>::bit_set();
        }

        static bool read_input_value()
        {
          // Read the port input value.
          volatile std::uint32_t pio_reg_status;
          pio_reg_status = mcal::reg::access<addr_type,
                                             reg_type,
                                             input_data_register,
                                             bpos>::reg_get();
          return ( pio_reg_status & static_cast<std::uint32_t>(UINT32_C(0x01) << (bpos)));
        }

        static void toggle_pin()
        {
          // Toggle the port output value.
          mcal::reg::access<addr_type,
                            reg_type,
                            clear_output_data,
                            bpos>::bit_not();
        }

      private:
        static constexpr addr_type port_enable_register         = addr_type(port + 0x00UL);
        static constexpr addr_type port_disable_register        = addr_type(port + 0x04UL);
        static constexpr addr_type port_status_register         = addr_type(port + 0x08UL);
        static constexpr addr_type output_enable_register       = addr_type(port + 0x10UL);
        static constexpr addr_type output_disable_register      = addr_type(port + 0x14UL);
        static constexpr addr_type glicth_filter_disable        = addr_type(port + 0x24UL);
        static constexpr addr_type set_output_data              = addr_type(port + 0x30UL);
        static constexpr addr_type clear_output_data            = addr_type(port + 0x34UL);
        static constexpr addr_type input_data_register          = addr_type(port + 0x3CUL);
        static constexpr addr_type interrupt_enable_register    = addr_type(port + 0x40UL);
        static constexpr addr_type interrupt_disable_register   = addr_type(port + 0x44UL);
        static constexpr addr_type pull_up_disable_register     = addr_type(port + 0x60UL);
        static constexpr addr_type pull_up_enable_register      = addr_type(port + 0x64UL);
        static constexpr addr_type pull_down_enable_register    = addr_type(port + 0x90UL);
        static constexpr addr_type pull_down_disable_register  = addr_type(port + 0x94UL);
        static constexpr addr_type peripheral_select_register   = addr_type(port + 0x70UL);
        static constexpr addr_type output_write_disable         = addr_type(port + 0xA4UL);

      };

      /*
      extern port_pin<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::piob_base,
                      UINT32_C(3) > aurt1_tx_pin;

      extern port_pin<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::pioa_base,
                      UINT32_C(4) > twi0_clock_pin;

      extern port_pin<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::pioa_base,
                      UINT32_C(3) > twi0_data_pin;
      *//*
      extern port_pin<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::piob_base,
                      UINT32_C(5) > twi1_clock_pin;

      extern port_pin<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::piob_base,
                      UINT32_C(4) > twi1_data_pin;
      */
      // Switch Buttom on Pin PA02
      /*
      extern port_pin<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::pioa_base,
                      UINT32_C(2) > sw0_button_pin;
*/
      // LED on port pin PIOA_14 LED1
      extern port_pin<std::uint32_t,
                           std::uint32_t,
                           mcal::reg::pioa_base,
                           UINT32_C(14) > led1_pin;

      // LED on port pin PIOA_15
      extern port_pin<std::uint32_t,
                           std::uint32_t,
                           mcal::reg::pioa_base,
                           UINT32_C(15) > led2_pin;

      extern port_pin<std::uint32_t,
                           std::uint32_t,
                           mcal::reg::pioa_base,
                           UINT32_C(26) > sw2_button_pin;

      extern port_pin<std::uint32_t,
                           std::uint32_t,
                           mcal::reg::pioa_base,
                           UINT32_C(13) > sw3_button_pin;
    }
  }

#endif // MCAL_PORT_2018_01_10_H_
