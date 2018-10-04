/**
 * @breif test STL circular buffer.
 * @author Juan Manuel Gomez <greenlean@protonmail.com>
 * @copyrigth 
 * g++ -std=c++11 -g -O2 -Wall -Wextra -fsigned-char -fno-exceptions -Isrc -o build/test_circular_buffer.o -c src/app/test_circular_buffer.cpp 
 * g++ -std=c++11 -g -O2 -Wall -Wextra -fsigned-char -fno-exceptions -Isrc  build/test_circular_buffer.o -o build/test_circular_buffer
 * ./build/test_circular_buffer 
 */


//#include <algorithm>
#include <iostream>
#include <iterator>
#include <my_util/util_communication.h>

constexpr uint32_t buffer_size = 32U;
typedef util::circular_buffer<std::uint8_t, buffer_size> buffer_type;

namespace 
{
buffer_type recv_buffer;
buffer_type send_buffer;
}

int main()
{

  std::uint8_t byte_to_send = 0, byte_to_recv = 0;
  for(int i = 0; i< 10; i ++)
  {
    byte_to_send = static_cast<uint8_t>(i);
    send_buffer.push_front(byte_to_send);
    std::cout << "Add value: " << static_cast<unsigned>(byte_to_send) << " to circular buffer." << std::endl;
  }

  if ( send_buffer.empty() )
  {

    std::cout << "Send buffer is empty." << std::endl;
  }
  /*  else
  {
    recv_buffer = send_buffer;

    for(auto it = recv_buffer.begin(); it != recv_buffer.end(); ++it) 
    {
      byte_to_recv = *it;
      std::cout << "Extract value: " << static_cast<unsigned>(byte_to_recv) << " from circular buffer." << std::endl;
    }
    }*/
  
}
