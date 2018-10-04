/*
 * @file buffer_communication.cpp
 * @brief Communication specialization for a vector buffer transmission.
 * @description Communication class definition for embedded system.
 * @return 
 * @author jmgomez@iaa.es
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

#include <buffer_communication.h>
#include <iostream>

util::comm::buffer_communication util::comm::my_buff_comm;

bool util::comm::buffer_communication::send(const std::uint8_t byte_to_send)
{
  if (!send_is_active)
  {
    send_is_active = true;
    send_buffer.push_back(byte_to_send);
    send_is_active = false;
    return true;
  }

  std::cout << "[buffer_communication]: Error send is busy.  " << std::endl; 
  return false;
}

template<typename send_iterator_type>
bool util::comm::buffer_communication::send_n(send_iterator_type first, send_iterator_type last)
{

  bool send_result = true;

  while(first != last)
  {
    typedef typename std::iterator_traits<send_iterator_type>::value_type send_value_type;

    const send_value_type value(*first);

    send_result &= send(value);

    if (!send_result)
      std::cout << "[buffer_communication] Error send_n why" << std::endl;

    ++first;
  }
  

  for ( const auto& s: send_buffer)
    std::cout << static_cast<unsigned>(s) << ", " ; 

  std::cout << std::endl;


  return send_result;

}

/*This is required to use the Template in the CPP file, we should check for code bloats.
One option migth be, move this function to the buffer_communication_base from which buffer_communication
should be derived. That allow to keep recv_n and send_n in the .h file. */
template bool util::comm::buffer_communication::send_n<std::uint8_t *>(std::uint8_t*, std::uint8_t *);

std::size_t util::comm::buffer_communication::recv_ready() const
{
  return recv_buffer.size();
}

bool util::comm::buffer_communication::recv(std::uint8_t& byte_to_recv)
{
  if ( recv_ready() )
  {
    //    for(auto it = recv_buffer.begin(); it != recv_buffer.end(); ++it) 
    //    {
    auto it = recv_buffer.begin();
    byte_to_recv = *it;
    recv_buffer.erase(it);
      //    }

    return true;
  }
  else
  {
    return false;
  }
    
}

template<typename recv_iterator_type>
bool util::comm::buffer_communication::recv_n(recv_iterator_type first, util::comm::buffer_communication::size_type count)
{
  const util::comm::buffer_communication::size_type count_to_recv = (std::min)(count, recv_ready());
  recv_iterator_type last = first + count_to_recv;

  bool recv_result = true;

  while(first != last)
  {
    std::uint8_t byte_to_recv;
    recv_result &= recv(byte_to_recv);

    typedef typename std::iterator_traits<recv_iterator_type>::value_type  recv_value_type;
    
    *first = recv_value_type(byte_to_recv);

    ++first;

  }

  return recv_result;

}


/*This is required to use the Template in the CPP file, we should check for code bloats.
One option migth be, move this function to the buffer_communication_base from which buffer_communication
should be derived. That allow to keep recv_n and send_n in the .h file. */
template bool util::comm::buffer_communication::recv_n<std::uint8_t *>(std::uint8_t*, std::size_t);


void util::comm::buffer_communication::simulate_recv()
{
  recv_buffer = send_buffer;
  send_buffer.clear();
}
