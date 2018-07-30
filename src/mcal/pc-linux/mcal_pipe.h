/**
 * @file mcal_pipe.h
 * @brief Abstraccion para comunicacion usando pipes
 * @description 
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#include <cstdint>
#include <iterator>
#include <util/utility/util_communication.h>

// Pipe Includes
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#ifndef _MCAL_PIPE_LINUX_2018_
#define _MCAL_PIPE_LINUX_2018_

namespace mcal
{

namespace pipe_comm
{
typedef void config_type;
typedef std::size_t size_type;
std::int32_t pipefd[2];

inline void init(const config_type *);
inline void close(const config_type *);

class pipe_communication : public util::communication<16U>
{
 public:
  pipe_communication();
  ~pipe_communication();

  bool send (const std::uint8_t byte_to_send) override;
  bool recv (std::uint8_t &byte_to_recv) override;

  size_type recv_ready() const;
  bool idle () const;
  
 private: 
  volatile bool send_is_active;

  std::int32_t wr_fd;
  std::int32_t rd_fd;
  buffer_type send_buffer;
  buffer_type recv_buffer;
    
};
  
  extern pipe_communication the_pipe;
}
}


#endif  //_MCAL_PIPE_LINUX_2018_
