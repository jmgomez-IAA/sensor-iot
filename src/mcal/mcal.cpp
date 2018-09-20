/**
 * @file mcal.cpp
 * @brief Microcontroller abstraction layer
 * @description Include the initialization and hardware
 * abstraction for the microcontroller.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include <mcal/mcal.h>

void mcal::init()
{
  //  mcal::cpu::init(nullptr);
  //mcal::irq::init(nullptr);
  //mcal::led::init(nullptr);


  mcal::fd::file_dev_params.output_filename = "out_file.bin";
  mcal::fd::file_dev_params.input_filename = "in_file.bin";

  //  file_dev_params.send_byte_buffer;
  //file_dev_params.recv_byte_buffer;

  mcal::fd::init( &mcal::fd::file_dev_params );
}
