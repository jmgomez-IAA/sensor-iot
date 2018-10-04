/**
 * @breif Linux inter process communication using pipes.
 * @author Juan Manuel Gomez <greenlean@protonmail.com>
 * @copyrigth 
 */

#include <string>
#include <iostream>

#include <mcal/mcal.h>


int main(int argc, char *argv[])
{

  std::uint32_t byte_to_send = 0, byte_to_recv = 0;
  for(int i = 0; i< 10; i ++)
  {
    mcal::pipe_comm::the_pipe.send( byte_to_send );

    mcal::pipe_comm::the_pipe_recv( byte_to_recv );

    std::cout << "Send the value : " << byte_to_send << " and received: " << byte_to_recv << std::endl;
  }

}
