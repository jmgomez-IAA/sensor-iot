/**
 * @breif Test communication using a file descriptor a device.
 * @Description May be used with /dev/ttyUSB0
 * @author Juan Manuel Gomez <greenlean@protonmail.com>
 * @copyrigth 
 * How-to build:
 *
 * g++ -std=c++11 -g -O2 -Wall -Wextra -fsigned-char -fno-exceptions -Isrc -o build/test_circular_buffer.o -c src/app/test_circular_buffer.cpp 
 * g++ -std=c++11 -g -O2 -Wall -Wextra -fsigned-char -fno-exceptions -Isrc  build/test_circular_buffer.o -o build/test_circular_buffer
 * ./build/test_circular_buffer 
 */


#include <iostream>
#include <fstream>  // for file I/O
#include <iomanip>  // for setw()
#include <cstdlib>  //for exit()

#include <string>

#include <mcal/mcal.h>


int main()
{

  mcal::init();


  mcal::fd::file_descriptor_communication fd_dev( mcal::fd::file_dev_params.send_byte_buffer,  mcal::fd::file_dev_params.recv_byte_buffer);
  std::uint8_t byte_to_tx;
  byte_to_tx = 65;
  fd_dev.send(byte_to_tx);


  std::uint8_t byte_to_rx;
  fd_dev.recv( byte_to_rx );
  std::cout << "Se recibio el byte: " << unsigned(byte_to_rx) << "." << std::endl;

  exit(0);
}
