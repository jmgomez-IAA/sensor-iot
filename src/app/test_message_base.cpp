/**
 * @breif test Message Interface for comunicationBase buffer.
 * @author Juan Manuel Gomez <greenlean@protonmail.com>
 * @copyrigth 
 * How-to build:
 *
 * g++ -std=c++11 -g -O2 -Wall -Wextra -fsigned-char -fno-exceptions -Isrc -o build/test_circular_buffer.o -c src/app/test_circular_buffer.cpp 
 * g++ -std=c++11 -g -O2 -Wall -Wextra -fsigned-char -fno-exceptions -Isrc  build/test_circular_buffer.o -o build/test_circular_buffer
 * ./build/test_message_base
 */


#include <iostream>
#include <vector>

#include <buffer_communication.h>

//#include <PipeMessage/PipeMessage.h>

//buffer_communication my_buff_comm;
//extern util::comm::buffer_communication util::comm::my_buff_comm;

int main()
{

  std::uint8_t byte_to_send = 0, byte_to_recv = 0;
  for(int i = 0; i< 10; i ++)
  {
    byte_to_send = static_cast<uint8_t>(i);

    util::comm::my_buff_comm.send(byte_to_send);
    std::cout << "Add value: " << static_cast<unsigned>(byte_to_send) << " to transmit." << std::endl;
  }

  util::comm::my_buff_comm.simulate_recv();

  std::size_t received_elements = 0;
  while ( (received_elements = util::comm::my_buff_comm.recv_ready()) != 0 )
  {
    
    std::cout << "There are " << received_elements << " received." << std::endl;

    if (util::comm::my_buff_comm.recv(byte_to_recv) )
    {
      std::cout << "Extract value: " << static_cast<unsigned>(byte_to_recv) << " from circular buffer." << std::endl;
    }
    else
    {
      std::cout << "Error." << std::endl;
    }
  }
  std::cout << "Send buffer is empty." << std::endl;
  
}
