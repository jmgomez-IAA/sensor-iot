/**
 * @file mcal_cpu.h
 * @brief Microcontroller abstraction layer for SAM4S ARM Cortex M CPU
 * @description Inicialization and definitions for the CPU ARM Cortex M4
 * abstraction layer for the microcontroller SAM4S.
 * @author Juan Manuel Gomez Lopez <jmgomez@iaa.es>
 * @copyright 
 */

#ifndef _MCAL_PCM_SAM4S_EMBEDDED_2018_
#define _MCAL_PCM_SAM4S_EMBEDDED_2018_


namespace mcal
{
  namespace pcm
  {
    typedef void config_type;
    void init(const config_type*);

  }
}


#endif  //_MCAL_PCM_SAM4S_EMBEDDED_2018
