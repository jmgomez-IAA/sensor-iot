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
<<<<<<< HEAD
  mcal::cpu::init();
=======
  //  mcal::cpu::init(nullptr);
>>>>>>> f8a6d1132afef27090a9c144b5c0aebe805de5a1
  //mcal::irq::init(nullptr);
  //mcal::led::init(nullptr);


  mcal::fd::file_dev_params.output_filename = "out_file.bin";
  mcal::fd::file_dev_params.input_filename = "in_file.bin";

  //  file_dev_params.send_byte_buffer;
  //file_dev_params.recv_byte_buffer;

  mcal::fd::init( &mcal::fd::file_dev_params );
}
