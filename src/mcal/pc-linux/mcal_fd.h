/**
 * @file mcal_fd.h
 * @brief Abstraccion para comunicacion usando pipes
 * @description 
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include <cstdint>
#include <iostream>

#include <util/utility/util_communication.h>

// File Includes
#include <fstream>  // for file I/O
#include <iomanip>  // for setw()
#include <cstdlib>  //for exit()

#ifndef _MCAL_FD_LINUX_2018_
#define _MCAL_FD_LINUX_2018_

namespace mcal
{
namespace fd
{

typedef void config_type;

void init(const config_type *);

class file_descriptor_communication : public communication
{
 public:
  //  typedef std::vector<std::uint8_t> buffer_type;
  typedef std::iostream buffer_type;
        
  file_descriptor_communication() : send_is_active(false) {}

  virtual bool send(const std::uint8_t byte_to_send);
  //template<typename send_iterator_type>
  // bool send_n(send_iterator_type first, send_iterator_type last);

  virtual std::size_t recv_ready() const;
  virtual bool recv(std::uint8_t &byte_to_recv);
  //bool recv_n(recv_iterator_type first,size_type count)
  void simulate_recv();

 private:
  volatile bool send_is_active;
  buffer_type send_buffer;
  buffer_type recv_buffer;
};
      
extern file_descriptor_communication my_fd_comm;
}
}


#endif  // _MCAL_FD_LINUX_2018_

