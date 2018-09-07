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
//#include <PipeMessage/PipeMessage.h>

//buffer_communication my_buff_comm;
//extern util::comm::buffer_communication util::comm::my_buff_comm;

int main()
{


std::ofstream file_out_desc( "out_dev_fd.bin" , (std::ios::out | std::ios::app | std::ios::ate | std::ios::binary ));
  if (! file_out_desc )
  {
    std::cerr << "Can't open the output file " << "out_dev_fd.bin"  << " " << std::endl;
    exit(EXIT_FAILURE);
  }

std::ifstream file_in_desc ( "in_dev_fd.bin" , (std::ios::in | std::ios::app | std::ios::binary) );
  if (! file_in_desc)
  {
    std::cerr << "Can't open the input file " << "out_dev_fd.bin"  << " " << std::endl;
    exit(EXIT_FAILURE);
  }  


  mcal::fd::file_descriptor_communication( file_out_desc, file_in_desc);

  
}
