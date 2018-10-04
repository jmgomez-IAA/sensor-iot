/*
 * @file buffer_communication.h
 * @brief Communication specialization for a vector buffer transmission.
 * @description Communication class definition for embedded system.
 * Biblio: https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 * @return 
 * @author jmgomez@iaa.es
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

//#include <iostream>
#include <cstdint>
#include <vector>
#include <iterator>
#include <algorithm>

#include <util_communication.h>

#ifndef _COMM_BUFF_2018_08_16_H_
#define _COMM_BUFF_2018_08_16_H_

namespace util
{
  namespace comm 
  {

      class buffer_communication : public communication
      {
       public:
        typedef std::vector<std::uint8_t> buffer_type;
        typedef std::size_t size_type;
        
        buffer_communication() : send_is_active(false) {}

        virtual bool send(const std::uint8_t byte_to_send);
        
        template<typename send_iterator_type>
        bool send_n(send_iterator_type first, send_iterator_type last);

        virtual std::size_t recv_ready() const;
        virtual bool recv(std::uint8_t &byte_to_recv);

        template<typename recv_iterator_type>
        bool recv_n(recv_iterator_type first,size_type count);

        void simulate_recv();

       private:
        volatile bool send_is_active;
        buffer_type send_buffer;
        buffer_type recv_buffer;
      };
      
      extern buffer_communication my_buff_comm;
  }
}


#endif // _COMM_BUFF_2018_08_16_H_
