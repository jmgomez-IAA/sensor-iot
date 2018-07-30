/**
 * @file mcal_pipe.cpp
 * @brief
 * @description
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright
 */

#include <mcal_pipe.h>


mcal::pipe_comm::pipe_communication mcal::pipe_comm::the_pipe;


inline void mcal::pipe_comm::init(const config_type*)
{
  //open the pipe
  pipe(mcal::pipe_comm::pipefd);

}

inline void mcal::pipe_comm::close(const config_type *)
{
  ::close(mcal::pipe_comm::pipefd[1]);
  ::close(mcal::pipe_comm::pipefd[0]);
}


mcal::pipe_comm::pipe_communication::pipe_communication() : wr_fd(mcal::pipe_comm::pipefd[1]),
                                                            rd_fd( mcal::pipe_comm::pipefd[0])
{
  send_is_active = false;
  
}

mcal::pipe_comm::pipe_communication::~pipe_communication()
{

  wr_fd = 0;
  rd_fd = 0;
}


bool mcal::pipe_comm::pipe_communication::send (const std::uint8_t byte_to_send)
{

  write(wr_fd, &byte_to_send, 1);
  return true;
}

bool mcal::pipe_comm::pipe_communication::recv (std::uint8_t &byte_to_recv)
{
 
  read(rd_fd, &byte_to_recv, 1);  
  return true;
}

mcal::pipe_comm::size_type mcal::pipe_comm::pipe_communication::recv_ready() const
{

  std::uint8_t byte_to_recv, byte_recv_count = 0;
  /*
  while (read(rd_fd, &byte_to_recv, 1) > 0 )
  {
    recv_buffer.push_front(byte_to_recv);
    byte_recv_count ++;
  }
  */
  return byte_recv_count;
}


bool mcal::pipe_comm::pipe_communication::idle() const
{
  return true;
}
