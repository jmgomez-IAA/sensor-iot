///////////////////////////////////////////////////////////////////////////////
//  Copyright Juan Manuel Gómez 2018

#include <array>
#include <cstddef>
#include <mcal_cpu.h>

extern "C" void __initial_stack_pointer();

extern "C" void __my_startup         () __attribute__((used, noinline));
extern "C" void __vector_unused_irq  () __attribute__((used, noinline));
extern "C" void __nmi_handler        () __attribute__((used, noinline));
extern "C" void __hard_fault_handler () __attribute__((used, noinline));
extern "C" void __mem_manage_handler () __attribute__((used, noinline));
extern "C" void __bus_fault_handler  () __attribute__((used, noinline));
extern "C" void __usage_fault_handler() __attribute__((used, noinline));
extern "C" void __svc_handler        () __attribute__((used, noinline));
extern "C" void __debug_mon_handler  () __attribute__((used, noinline));
extern "C" void __pend_sv_handler    () __attribute__((used, noinline));
extern "C" void __sys_tick_handler   () __attribute__((used, noinline));
extern "C" void __vector_timer4      () __attribute__((used, noinline));

// Unused irq simply halts.

extern "C" void __vector_unused_irq  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __nmi_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __hard_fault_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __mem_manage_handler () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __bus_fault_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __usage_fault_handler() { for(;;) { mcal::cpu::nop(); } }
extern "C" void __svc_handler        () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __debug_mon_handler  () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __pend_sv_handler    () { for(;;) { mcal::cpu::nop(); } }
extern "C" void __sys_tick_handler   () { for(;;) { mcal::cpu::nop(); } }

namespace
{
  typedef void (*isr_type)();

  //There are only 35, pag 196 datasheet, but there are space so!!
  constexpr std::size_t number_of_interrupts = 51U;
}

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector =
{{
  __initial_stack_pointer,   // 0x0000, initial stack pointer
  __my_startup,              // 0x0004, reset
  __nmi_handler,             // 0x0008, nmi exception
  __hard_fault_handler,      // 0x000C, hard fault exception
  __mem_manage_handler,      // 0x0010, memory management exception
  __bus_fault_handler,       // 0x0014, bus fault exception
  __usage_fault_handler,     // 0x0018, usage fault exception
  __vector_unused_irq,       // 0x001C, reserved
  __vector_unused_irq,       // 0x0020, reserved
  __vector_unused_irq,       // 0x0024, reserved
  __vector_unused_irq,       // 0x0028, reserved
  __svc_handler,             // 0x002C, svc handler
  __debug_mon_handler,       // 0x0030, debug monitor
  __vector_unused_irq,       // 0x0034, reserved
  __pend_sv_handler,         // 0x0038, pending svc,
  __sys_tick_handler,        // 0x003C, system tick handler,
  __vector_unused_irq,       // 0x0040, wwdg irq handler, 0_supplyCtrl
  __vector_unused_irq,       // 0x0044, pvd irq handler, 1_rstCtrl
  __vector_unused_irq,       // 0x0048, tamper irq handler, 2 RTC
  __vector_unused_irq,       // 0x004C, rtc irq handler, 3 RTT
  __vector_unused_irq,       // 0x0050, flash irq handler, 4 wdg
  __vector_unused_irq,       // 0x0054, rcc irq handler, 5 pmc
  __vector_unused_irq,       // 0x0058, exti0 irq handler, 6 eefc0
  __vector_unused_irq,       // 0x005C, exti1 irq handler, 7 eefc1
  __vector_unused_irq,       // 0x0060, exti2 irq handler, uart0
  __vector_unused_irq,       // 0x0064, exti3 irq handler, uart1
  __vector_unused_irq,       // 0x0068, exti4 irq handler,
  __vector_unused_irq,       // 0x006C, dma_channel1 irq handler, PIOA
  __vector_unused_irq,       // 0x0070, dma_channel2 irq handler, PIOB
  __vector_unused_irq,       // 0x0074, dma_channel3 irq handler, PIOC
  __vector_unused_irq,       // 0x0078, dma_channel4 irq handler, USART0
  __vector_unused_irq,       // 0x007C, dma_channel5 irq handler, USART1
  __vector_unused_irq,       // 0x0080, dma_channel6 irq handler,
  __vector_unused_irq,       // 0x0084, dma_channel7 irq handler,
  __vector_unused_irq,       // 0x0088, adc irq handler, mci
  __vector_unused_irq,       // 0x008C, usb_hp_can_tx irq handler, twi0
  __vector_unused_irq,       // 0x0090, usb_lp_can_rx0 irq handler, twi1
  __vector_unused_irq,       // 0x0094, can_rx1 irq handler, spi
  __vector_unused_irq,       // 0x0098, can_sce irq handler, ssc
  __vector_unused_irq,       // 0x009C, exti9_5 irq handler, tc0
  __vector_unused_irq,       // 0x00A0, tim1_brk irq handler,tc1
  __vector_unused_irq,       // 0x00A4, tim1_up irq handler, tc2
  __vector_unused_irq,       // 0x00A8, tim1_trg_com irq handler, tc3
  __vector_unused_irq,       // 0x00AC, tim1_cc irq handler, tc4
  __vector_unused_irq,       // 0x00B0, tim2 irq handler, tc5
  __vector_unused_irq,       // 0x00B4, tim3 irq handler, adc
  __vector_unused_irq,       // 0x00B8, tim4 irq handler, dac
  __vector_unused_irq,       // 0x00BC, i2c1_ev irq handler, pwm
  __vector_unused_irq,       // 0x00C0, i2c1_er irq handler, crc
  __vector_unused_irq,       // 0x00C4, i2c2_ev irq handler, analog
  __vector_unused_irq       // 0x00C8, i2c2_er irq handler, usb dev port
}};
