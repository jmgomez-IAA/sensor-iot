/**
 * @file mcal_gpt.h
 * @brief Timer module abstraction layer for SAM4S
 * @description Inicialization and definitions for the Timer module
 * abstraction layer for the microcontroller SAM4S.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_GPT_SAM4S_EMBEDDED_2018_
#define _MCAL_GPT_SAM4S_EMBEDDED_2018_

namespace mcal
{
  namespace gpt
  {
    typedef void config_type;
    void init(const config_type*);
  }
}


#endif  //_MCAL_GPT_SAM4S_EMBEDDED_2018
