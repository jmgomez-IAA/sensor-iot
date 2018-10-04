/*
 * @file buffer_communication.cpp
 * @brief Communication specialization for a vector buffer transmission.
 * @description Communication class definition for embedded system.
 * @return 
 * @author jmgomez@iaa.es
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */




#include <buffer_communication.h>

util::comm::buffer_communication util::comm::my_buff_comm;

bool util::comm::buffer_communication::send(const std::uint8_t byte_to_send){
  if (!send_is_active)
  {
    send_is_active = true;
    send_buffer.push_back(byte_to_send);
    send_is_active = false;
    return true;
  }

  return false;
}

std::size_t util::comm::buffer_communication::recv_ready() const
{
  return recv_buffer.size();
}

bool util::comm::buffer_communication::recv(std::uint8_t &byte_to_recv){
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

void util::comm::buffer_communication::simulate_recv()
{
  recv_buffer = send_buffer;
  send_buffer.clear();
}
