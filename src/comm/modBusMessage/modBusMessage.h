/*
 * @file ModbusMessage.h
 * @brief Message comunication using MODBUS protocol.
 * @description 
 * @author greenlean
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

#ifndef _COMM_MODBUS_2018_08_16_H_
#define _COMM_MODBUS_2018_08_16_H_


#include <iostream>
#include <assert.h>

#include "../Message.h"

namespace comm 
{
  namespace msg
  {

    void init(void *void_ptr);

    template<typename TReadIter, typename TWriteIter>
    class ModbusMessage : public Message<TReadIter, TWriteIter>
    {

    public:
      //      using Base = Message<TReadIter,TWriteIter>;
      //using ReadIterator = Base::ReadIterator;
      //using WriteIterator = Base::WriteIterator;
      enum MODBUS_Function_Codes : std::uint8_t 
      {
        not_supported_function = 0x00,
            read_coils  = 0x01, 
            read_discrete_inputs  = 0x02,
            read_holding_registers  = 0x03, 
            read_input_register  = 0x04,
            write_single_coil = 0x05, 
            write_single_register = 0x06,
            write_multiple_coils = 0x0F,
            write_multiple_registers = 0x10            
      };

      using ReadIterator = TReadIter;
      using WriteIterator = TWriteIter;


      ModbusMessage(std::uint32_t id, std::int32_t t, std::uint32_t h): MsgId(id), temp(t), humidity(h){};

      void ShowFields()
      {
	std::cout << "M: " << MsgId << "T: " << temp << "H: " << humidity << std::endl;
      }

      ~ModbusMessage() {MsgId=0; temp=0; humidity=0;};

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

	for(int i=0; i<len; ++i)
	  {
	    if (i==0)	     
	      MsgId = static_cast<std::uint32_t>(*iter);

	    if (i==1)	     
	      temp = static_cast<std::int32_t>(*iter);

	    if (i==2)	     
	      humidity = static_cast<std::int32_t>(*iter);

	    iter ++;
	  }
	
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
        assert(len < 256); // Message size is limited to 256 bytes. PDU_Max_Size = 256 - ADDR - CRC.

	(*iter) = MsgId;
	iter ++;
        (*iter) = temp;
	iter ++;
        (*iter) = humidity;
	iter++;

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
    private:
      //RS485 ADU= 253 bytes + Server address (1 byte) + CRC (2 bytes) = 256 bytes

      //The data in the message is Temperatura, Humidity and Others
      std::uint32_t additional_addr;
      array<std::uint8_t,253> rs485_adu;
      std::uint32_t crc;

      
      virtual comm::ErrorStatus create_mb_req_pdu(MODBUS_Function_Codes function_code, array<std::uint8_t>request_data);
      virtual comm::ErrorStatus create_mb_rsp_pdu(MODBUS_Function_Codes function_code, array<std::uint8_t>request_data);
      virtual comm::ErrorStatus create_excep_rsp_pdu(MODBUS_Function_Codes function_code, array<std::uint8_t>request_data);

    };

  }
}

#endif //__COMM_MSG_2018_06_16_H_
