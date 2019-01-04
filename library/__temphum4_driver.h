/*
    __temphum4_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __temphum4_driver.h
@brief    TempHum4 Driver
@mainpage TempHum4 Click
@{

@image html sch.jpg

@}

@defgroup   TEMPHUM4
@brief      TempHum4 Click Driver
@{

| Global Library Prefix | **TEMPHUM4** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Jan 2018.**      |
| Developer             | **MikroE Team**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _TEMPHUM4_H_
#define _TEMPHUM4_H_

/** 
 * @macro T_TEMPHUM4_P
 * @brief Driver Abstract type 
 */
#define T_TEMPHUM4_P    const uint8_t*

/** @defgroup TEMPHUM4_COMPILE Compilation Config */              /** @{ */

//  #define   __TEMPHUM4_DRV_SPI__                            /**<     @macro __TEMPHUM4_DRV_SPI__  @brief SPI driver selector */
   #define   __TEMPHUM4_DRV_I2C__                            /**<     @macro __TEMPHUM4_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __TEMPHUM4_DRV_UART__                           /**<     @macro __TEMPHUM4_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup TEMPHUM4_VAR Variables */                           /** @{ */


extern const uint8_t _TEMPHUM4_MODE_ACTIVE;
extern const uint8_t _TEMPHUM4_MODE_SLEEP;

extern const uint8_t _TEMPHUM4_REG_TEMPERATURE;
extern const uint8_t _TEMPHUM4_REG_HUMINIDY;
extern const uint8_t _TEMPHUM4_REG_CONFIGURATION;
extern const uint8_t _TEMPHUM4_REG_MANUFACTURER_ID;
extern const uint8_t _TEMPHUM4_REG_DEVICE_ID;
extern const uint8_t _TEMPHUM4_REG_SERIAL_ID;

extern const uint8_t _TEMPHUM4_CONF_NORMAL_OPERATION;
extern const uint8_t _TEMPHUM4_CONF_SOFT_RESET;
extern const uint8_t _TEMPHUM4_CONF_HEATER_DISABLED;
extern const uint8_t _TEMPHUM4_CONF_HEATER_ENABLED;
extern const uint8_t _TEMPHUM4_CONF_MODE_TEMP_OR_HUM;
extern const uint8_t _TEMPHUM4_CONF_MODE_TEMP_AND_HUM;
extern const uint8_t _TEMPHUM4_CONF_BATTERY_VOLTAGE_2_8_V;
extern const uint8_t _TEMPHUM4_CONF_TEMPERATURE_14bit;
extern const uint8_t _TEMPHUM4_CONF_TEMPERATURE_11bit;
extern const uint8_t _TEMPHUM4_CONF_HUMINIDY_14bit;
extern const uint8_t _TEMPHUM4_CONF_HUMINIDY_11bit;
extern const uint8_t _TEMPHUM4_CONF_HUMINIDY_9bit;

                                                                       /** @} */

#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup TEMPHUM4_INIT Driver Initialization */              /** @{ */

#ifdef   __TEMPHUM4_DRV_SPI__
void temphum4_spiDriverInit(T_TEMPHUM4_P gpioObj, T_TEMPHUM4_P spiObj);
#endif
#ifdef   __TEMPHUM4_DRV_I2C__
void temphum4_i2cDriverInit(T_TEMPHUM4_P gpioObj, T_TEMPHUM4_P i2cObj, uint8_t slave);
#endif
#ifdef   __TEMPHUM4_DRV_UART__
void temphum4_uartDriverInit(T_TEMPHUM4_P gpioObj, T_TEMPHUM4_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void temphum4_gpioDriverInit(T_TEMPHUM4_P gpioObj);
                                                                       /** @} */
/** @defgroup TEMPHUM4_FUNC Driver Functions */                   /** @{ */

/**
 * @brief This function for reads Manifacturer ID
 *
 * @return Manufacturer ID (0x5449) - ID of Texas Instruments
 */
uint16_t temphum4_getManifacturerID();
/**
 * @brief This function for reads Device ID
 *
 * @return Device ID (0x1000) - ID of HDC1010 device
 */
uint16_t temphum4_getDeviceID();

/**
 * @brief This function for reads Temperature
 *
 * @return Temperature data in C
 */
float temphum4_getTemperature();
/**
 * @brief This function for reads Huminidy
 *
 * @return Huminidy data in %RH
 */
float temphum4_getHuminidy();

/**
 * @brief This function for configuration measurement
 *
 * Options:
      Software reset (Normal Operation or Software Reset ),
      Heater (Heater enabled or Heater disabled),
      Mode of acquisition ( Temperature or Humidity is acquired or
                           Temperature and Humidity are acquired in sequence, Temperature first.),
      Battery Status (Battery voltage > 2.8V - (default) or Battery voltage < 2.8V ),
      Temperature measurement resolution( 14 bit or 11 bit),
      Humidity measurement resolution ( 14 bit, 11 bit or 9 bit ).
      
 */
void temphum4_Configuration(uint16_t _data);

/**
 * @brief This function settings mode
 *
 * Options:
      Mode ACTIVE,
      Mode SLEEP
 */
void temphum4_setMode(uint8_t value);




                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_TempHum4_STM.c
    @example Click_TempHum4_TIVA.c
    @example Click_TempHum4_CEC.c
    @example Click_TempHum4_KINETIS.c
    @example Click_TempHum4_MSP.c
    @example Click_TempHum4_PIC.c
    @example Click_TempHum4_PIC32.c
    @example Click_TempHum4_DSPIC.c
    @example Click_TempHum4_AVR.c
    @example Click_TempHum4_FT90x.c
    @example Click_TempHum4_STM.mbas
    @example Click_TempHum4_TIVA.mbas
    @example Click_TempHum4_CEC.mbas
    @example Click_TempHum4_KINETIS.mbas
    @example Click_TempHum4_MSP.mbas
    @example Click_TempHum4_PIC.mbas
    @example Click_TempHum4_PIC32.mbas
    @example Click_TempHum4_DSPIC.mbas
    @example Click_TempHum4_AVR.mbas
    @example Click_TempHum4_FT90x.mbas
    @example Click_TempHum4_STM.mpas
    @example Click_TempHum4_TIVA.mpas
    @example Click_TempHum4_CEC.mpas
    @example Click_TempHum4_KINETIS.mpas
    @example Click_TempHum4_MSP.mpas
    @example Click_TempHum4_PIC.mpas
    @example Click_TempHum4_PIC32.mpas
    @example Click_TempHum4_DSPIC.mpas
    @example Click_TempHum4_AVR.mpas
    @example Click_TempHum4_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __temphum4_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */