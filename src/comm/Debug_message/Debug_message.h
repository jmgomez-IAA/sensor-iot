/*
 * @file ModbusMessage.h
 * @brief Message comunication using MODBUS protocol.
 * @description 
 * @author greenlean
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

#ifndef _COMM_DBG_2018_08_16_H_
#define _COMM_DBG_2018_08_16_H_


#include <iostream>
#include <assert.h>
#include <array>

#include "../Message.h"

namespace comm 
{
namespace msg
{

void init(void *void_ptr);

template<typename TReadIter, typename TWriteIter>
class Debug_message : public Message<TReadIter, TWriteIter>
{

 public:
  // Candidate to move to template parameter.
  typedef std::array<uint8_t, 10> buffer_type;

  enum Debug_Message_Codes : std::uint8_t 
  {
    unknown = 0x00,
        log  = 0x01
        };

  using ReadIterator = TReadIter;
  using WriteIterator = TWriteIter;

  Debug_message(): log_message({'T','E','S','T'}){};
  ~Debug_message() {};

  /**
   * @brief Read a Message
   * @param Message to tran, ITerator, etc.
   * @return Communication Status, ErrorStatus enum.        
   *
   * NOTA: Este read impl ya dispone de array para la transmissión, podemos emplearlo y envar al 
   * device solo los iteradores y emplear la funcion read_n(iter, iter).
   */      
  virtual comm::ErrorStatus readImpl(ReadIterator &iter, std::size_t len)  override 
  {
	
    assert(0 < len < 64); // Message size is limited to 64 Bytes.
   
    ReadIterator last_element  = iter + len;

    std::cout << std::endl;
    while(iter != last_element)
    {
      std::cout << static_cast<unsigned>(*iter) << " ";
      iter++;
    }
    std::cout << std::endl;
    
    return comm::ErrorStatus::Success;
  };

  /**
   * @brief Write a Message
   * @param Message to transmit, ITerator, etc.
   * @return Communication Status, ErrorStatus enum.        
   *
   * NOTA: Este read impl ya dispone de array para la transmissión, podemos emplearlo y envar al 
   * device solo los iteradores y emplear la funcion read_n(iter, iter).
   */      
  virtual comm::ErrorStatus writeImpl(WriteIterator &iter, std::size_t len) override 
  {
    assert(0 < len < 64); // Message size is limited to 64 Bytes.

    std::uint32_t number_byte_to_send = 0;
    for( const auto& c : log_message )
    {

      if (number_byte_to_send < len)
      {
        (*iter) = c;
        number_byte_to_send ++;
        iter ++;
      }
      else
      {
        return comm::ErrorStatus::BufferOverflow;
      }

    }
    return comm::ErrorStatus::Success;
      
  };

  /**
   * @brief Process the Message!!
   */
  /*
    virtual comm::ErrorStatus dispatchImpl(Handler& handler) override
    {
    //....
    //handler.handle(*this);
	
    };
  */
  void print()
  {
    //PRINT_ELEMENTS<array<std::uint8_t,64>>(log_message);
    std::cout << std::endl;
    for (const auto& elem : log_message)
      std::cout << static_cast<unsigned>(elem) << " ";

    std::cout << std::endl;
  }

  void printAll()
  {
    
    util::aux::PRINT_ELEMENTS<buffer_type>(log_message);
    /*
      template <typename T>
      friend inline void util::aux::PRINT_ELEMENTS (const T& coll,
                                                    const std::string& optstr="");  
    */

  }

 private:

  buffer_type log_message;

};

}
}

#endif //__COMM_MSG_2018_06_16_H_
