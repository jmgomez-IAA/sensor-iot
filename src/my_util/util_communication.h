/*
 * @file util_communication.h
 * @brief Message Communication Base Class
 * @description Communication class definition for embedded system. The message interface may include the following operation:
 * - Retreive the message ID.
 * - Read (deserialize) the message contents into a buffer.
 * - Write (serialize) the message contents into a buffer.
 * - Calculate the serialization length of the message.
 * - Dispatch the message to an appropiate handling function.
 * - Check the validity of the message contents.
 * Some customization may be required and some functionalities may be skipped.
 * @return An enum class is create with the most frequente errors.
 * @author greenlean
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

class communication
{
 public:
 
  communication() : recv_buf(0U), has_recv(false) {}

  ~communication() {};

  bool send_byte(const std::uint8_t by) const
  {
    *reinterpret_cast<volatile std::uint8_t*>(tbuf) = by;
  }

  bool recv_ready() const {return has_recv;}

  std::uint8_t recv_byte()
  {
    if(has_recv)
    {
      has_recv = false;
      return recv_buf;
    }
    
    return 0U;
  }

 private:
  static constexpr std::uint8_t tbuf = 0xAAU;
  static constexpr std::uint8_t rbuf = 0xAEU;

  std::uint8_t recv_buf;
  bool has_recv;
  
  communication(const communication &) = delete;
  const communication& operator=(const communication&) = delete;

};


