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
#include <array>

#include <buffer_communication.h>

//#include <PipeMessage/PipeMessage.h>

//buffer_communication my_buff_comm;
//extern util::comm::buffer_communication util::comm::my_buff_comm;

constexpr std::size_t buffer_max_size = 64;
typedef std::array<uint8_t, buffer_max_size> buffer_type;

int main()
{

  std::uint8_t byte_to_send = 0, byte_to_recv = 0;
  buffer_type transmit_buffer;
  buffer_type receive_buffer;

  std::cout << "Test 1: Single byte transmission." << std::endl;
  std::cout << " ==============================  " << std::endl;

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


  std::cout << "Test 2: Multiple byte transmission." << std::endl;
  std::cout << " ================================  " << std::endl;
  
  std::uint8_t data_sample;
  for(auto it = transmit_buffer.begin(); it != transmit_buffer.end() ; it ++)
  {
    byte_to_send = static_cast<uint8_t>(data_sample);
    (*it) = data_sample;
    data_sample ++;
  }

  util::comm::my_buff_comm.send_n<std::uint8_t>(byte_to_send);
  //template<typename send_iterator_type>
  bool transfer_result = util::comm::send_n(transmit_buffer.begin(), transmit_buffer.end() );
  if (transfer_result)
    std::cout << "All bytes were transfered successfully. " << std::endl;

  util::comm::my_buff_comm.simulate_recv();

  return 0;
  

}
