/*
 * @file mcal_fd.cpp
 * @brief Communication specialization for a file transmission.
 * @description Communication class definition for embedded system.
 * @return 
 * @author jmgomez@iaa.es
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

#include <mcal_fd.h>

mcal::fd::config_type mcal::fd::file_dev_params;
//mcal::fd::file_descriptor_communication mcal::fd::my_fd_comm(file_dev_params.send, file_dev_params.recev, false);

void mcal::fd::init(config_type *params){

  if (params == nullptr )
    exit(EXIT_FAILURE);

  //  std::ofstream file_out_desc( "out_dev_fd.bin" , (std::ios::out | std::ios::app | std::ios::ate | std::ios::binary ));
  params->send_byte_buffer.open( "out_dev_fd.bin" , (std::ios::out | std::ios::app | std::ios::ate | std::ios::binary ));
  if (! params->send_byte_buffer.is_open() )
  {
    std::cerr << "Can't open the output file " << "out_dev_fd.bin"  << " " << std::endl;
    exit(EXIT_FAILURE);
  }

  //std::ifstream file_in_desc ( "in_dev_fd.bin" , (std::ios::in | std::ios::app | std::ios::binary) );
  params->recv_byte_buffer.open( "in_dev_fd.bin" , (std::ios::in | std::ios::app | std::ios::binary) );
  if (! params->recv_byte_buffer.is_open())
  {
    std::cerr << "Can't open the input file " << "out_dev_fd.bin"  << " " << std::endl;
    exit(EXIT_FAILURE);
  }  

  return;
};

/*
void mcal::fd::init(const config_type * channel_descriptor)
{

  if (channel_descriptor == nullptr ){
    exit(EXIT_FAILURE);
  }
  else
  {    
    
    channel_descriptor->send.open ( channel_descriptor->output_filename , (std::ios::out | std::ios::app | std::ios::ate | std::ios::binary ));
    if (! channel_descriptor->send )
    {
      std::cerr << "Can't open the output file " << channel_descriptor->output_filename  << " " << std::endl;
      exit(EXIT_FAILURE);
    }

    channel_descriptor->recv.input_file.open ( channel_descriptor->input_filename , (std::ios::in | std::ios::app | std::ios::binary) );
    if (! channel_descriptor->recv)
    {
      std::cerr << "Can't open the input file " << channel_descriptor->output_filename  << " " << std::endl;
      exit(EXIT_FAILURE);
    }  
  }
  //File is closed outmatically.
}
*/


bool mcal::fd::file_descriptor_communication::send(const std::uint8_t byte_to_send){
  if (!send_is_active)
  {
    send_is_active = true;

    if ( (send_buffer.rdstate() & std::ofstream::failbit ) != 0 ){
      std::cout << "Send error to the output file." << std::endl;
      return false;
    }
    //    send_buffer.push_back(byte_to_send);
    //    send_buffer.seekg(std::ios::end);
    char c = static_cast<char>(byte_to_send);
    send_buffer.put(c);
    send_buffer.flush();

    if ( (send_buffer.rdstate() & (std::ofstream::failbit | std::ofstream::badbit )) != 0 ){
      std::cout << "Send error to the output file." << std::endl;
      return false;
    }

    send_is_active = false;
    std::cout << "Wrote to the output file " << c  << "." << std::endl;

    

    return true;
  }

  return false;
}

std::size_t  mcal::fd::file_descriptor_communication::recv_ready() const
{
  const char nc = recv_buffer.peek();
  if ( nc != EOF)    // std::ifstream::eofbit
    return 1; // recv_buffer.size();
  else 
    return 0;
}

bool  mcal::fd::file_descriptor_communication::recv(std::uint8_t &byte_to_recv){
  if ( recv_ready() )
  {
    //    for(auto it = recv_buffer.begin(); it != recv_buffer.end(); ++it) 
    //    {

    //    recv_buffer.seekg( std::ios::beg);

    char c;
    recv_buffer.get(c);
    byte_to_recv = static_cast<std::uint8_t>(c);

    //    recv_buffer.erase(it);
      //    }

    return true;
  }
  else
  {
    return false;
  }
    
}

void  mcal::fd::file_descriptor_communication::simulate_recv()
{
  //  recv_buffer = send_buffer;
  //send_buffer.clear();
}
