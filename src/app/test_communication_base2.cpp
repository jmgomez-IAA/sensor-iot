/**
 * @breif test STL Comm Mesage Base buffer.
 * @author Juan Manuel Gomez <greenlean@protonmail.com>
 * @copyrigth 
 * How-to build:
 *
 * g++ -std=c++11 -g -O2 -Wall -Wextra -fsigned-char -fno-exceptions -Isrc -o build/test_circular_buffer.o -c src/app/test_circular_buffer.cpp 
 * g++ -std=c++11 -g -O2 -Wall -Wextra -fsigned-char -fno-exceptions -Isrc  build/test_circular_buffer.o -o build/test_circular_buffer
 * ./build/test_circular_buffer 
 */


#include <iostream>
#include <array>

#include <buffer_communication.h>

#include <Debug_message/Debug_message.h>

constexpr std::size_t buffer_max_size = 64;
typedef std::array<uint8_t, buffer_max_size> buffer_type;

typedef comm::msg::Debug_message<std::uint8_t*, std::uint8_t*> log_type;
typedef comm::msg::Message<std::uint8_t*, std::uint8_t*>* msg_type;

int main()
{

  buffer_type transmit_buffer;
  buffer_type receive_buffer;

  log_type system_log;
  msg_type msg_ptr = &system_log;

  //  system_log.print();
  system_log.printAll();

  std::cout << "Test 2: Multiple byte transmission." << std::endl;
  std::cout << " ================================  " << std::endl;
  
  std::uint8_t data_sample;
  std::uint8_t byte_to_send = 0, byte_to_recv = 0;
  /*
  for(auto it = transmit_buffer.begin(); it != transmit_buffer.end() ; it ++)
  {
    byte_to_send = static_cast<uint8_t>(data_sample);
    (*it) = data_sample;
    std::cout << "transmit_buffer.at( "<< static_cast<unsigned>(it - transmit_buffer.begin()) <<  ")= " << static_cast<unsigned>(data_sample) << std::endl;
    data_sample ++;
  }
  */

  buffer_type::iterator it_array = transmit_buffer.begin();
  system_log.writeImpl( it_array, static_cast< std::size_t>(10));
  //msg_ptr->writeImpl( transmit_buffer.begin()&, static_cast< std::size_t>(10));

  /*
  for ( const auto& s: transmit_buffer)
    std::cout << static_cast<unsigned>(s) << ", " ; 

  std::cout << std::endl;
  */
  //template<typename send_iterator_type>
  bool transfer_result = util::comm::my_buff_comm.send_n(transmit_buffer.begin(), (transmit_buffer.begin()+10) );
  if (transfer_result)
  {
    std::cout << "All bytes were transfered successfully. " << std::endl;
  }
  else
  {
    std::cout << "Error send_n." << std::endl;
    return 0;
  }

  util::comm::my_buff_comm.simulate_recv();  


  const std::size_t received_elements = util::comm::my_buff_comm.recv_ready();
  std::cout << "There are " << received_elements << " received." << std::endl;

  const bool recv_result = util::comm::my_buff_comm.recv_n(receive_buffer.begin(), received_elements);

  if (recv_result)
  {
    //    for ( const auto& r: receive_buffer)
    //  std::cout << "Extract value: " << static_cast<unsigned>(r) << " from receive channel." << std::endl;
    buffer_type::iterator first_iter = receive_buffer.begin();
    system_log.readImpl( first_iter, received_elements);

  }
  else
  {
    std::cout << "Error." << std::endl;
  } 

}
