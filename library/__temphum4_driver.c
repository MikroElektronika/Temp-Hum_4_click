/*
    __temphum4_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__temphum4_driver.h"
#include "__temphum4_hal.c"

/* ------------------------------------------------------------------- MACROS */

// MODE
const uint8_t _TEMPHUM4_MODE_ACTIVE = 0x01;
const uint8_t _TEMPHUM4_MODE_SLEEP  = 0x00;

// REG
const uint8_t _TEMPHUM4_REG_TEMPERATURE     = 0x00;
const uint8_t _TEMPHUM4_REG_HUMINIDY        = 0x01;
const uint8_t _TEMPHUM4_REG_CONFIGURATION   = 0x02;
const uint8_t _TEMPHUM4_REG_MANUFACTURER_ID = 0xFE;
const uint8_t _TEMPHUM4_REG_DEVICE_ID       = 0xFF;
const uint8_t _TEMPHUM4_REG_SERIAL_ID       = 0xFB;

// CONFIGURATION
const uint8_t _TEMPHUM4_CONF_NORMAL_OPERATION       = 0x00 << 14;
const uint8_t _TEMPHUM4_CONF_SOFT_RESET             = 0x01 << 14;
const uint8_t _TEMPHUM4_CONF_HEATER_DISABLED        = 0x00 << 12;
const uint8_t _TEMPHUM4_CONF_HEATER_ENABLED         = 0x01 << 12;
const uint8_t _TEMPHUM4_CONF_MODE_TEMP_OR_HUM       = 0x00 << 11;
const uint8_t _TEMPHUM4_CONF_MODE_TEMP_AND_HUM      = 0x01 << 11;
const uint8_t _TEMPHUM4_CONF_BATTERY_VOLTAGE_2_8_V  = 0x00 << 10;
const uint8_t _TEMPHUM4_CONF_TEMPERATURE_14bit      = 0x00 << 9;
const uint8_t _TEMPHUM4_CONF_TEMPERATURE_11bit      = 0x01 << 9;
const uint8_t _TEMPHUM4_CONF_HUMINIDY_14bit         = 0x00 << 7;
const uint8_t _TEMPHUM4_CONF_HUMINIDY_11bit         = 0x01 << 7;
const uint8_t _TEMPHUM4_CONF_HUMINIDY_9bit          = 0x02 << 7;


/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __TEMPHUM4_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __TEMPHUM4_DRV_SPI__

void temphum4_spiDriverInit(T_TEMPHUM4_P gpioObj, T_TEMPHUM4_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __TEMPHUM4_DRV_I2C__

void temphum4_i2cDriverInit(T_TEMPHUM4_P gpioObj, T_TEMPHUM4_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    hal_gpio_csSet(0);
    hal_gpio_rstSet(0);

}

#endif
#ifdef   __TEMPHUM4_DRV_UART__

void temphum4_uartDriverInit(T_TEMPHUM4_P gpioObj, T_TEMPHUM4_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif



/* ----------------------------------------------------------- IMPLEMENTATION */

void temphum4_setMode(uint8_t value)
{
    hal_gpio_csSet(value);
}

uint16_t temphum4_getManifacturerID()
{
    uint8_t readReg[2];
    uint8_t writeReg[1];
    uint16_t MainID;
    writeReg[0] = 0xFE;
    
    if( hal_gpio_intGet() )
    {
        hal_i2cStart();
        hal_i2cWrite(_slaveAddress, writeReg, 1, END_MODE_RESTART);
        Delay_100ms();
        hal_i2cRead(_slaveAddress, readReg, 2, END_MODE_STOP);
    
       MainID = readReg[0];
       MainID <<= 8;
       MainID = MainID | readReg[1];
    
      Delay_100ms();
    }
    return MainID;
}

uint16_t temphum4_getDeviceID()
{
    uint8_t readReg[2];
    uint8_t writeReg[1];
    uint16_t DeviceID = 0;
    writeReg[0] = 0xFF;
    
    if( hal_gpio_intGet() )
    {
        hal_i2cStart();
        hal_i2cWrite(_slaveAddress, writeReg, 1, END_MODE_RESTART);
        Delay_100ms();
        hal_i2cRead(_slaveAddress, readReg, 2, END_MODE_STOP);

        DeviceID = readReg[0];
        DeviceID <<= 8;
        DeviceID = DeviceID | readReg[1];

        Delay_100ms();
    }
    return DeviceID;
}

void temphum4_Configuration(uint16_t _data)
{
    uint8_t writeReg[3];
    writeReg[0]  = 0x02;
    writeReg[1] = _data >> 8;
    writeReg[2] = _data;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeReg, 3, END_MODE_STOP);
    Delay_100ms();
}

float temphum4_getTemperature()
{
    uint8_t wReg[1];
    uint8_t rReg[2];
    volatile int16_t tempData;
    volatile float temp;
    wReg[0] = 0x00;

    if( hal_gpio_intGet() )
    {
        hal_i2cStart();
        hal_i2cWrite(_slaveAddress, wReg, 1, END_MODE_RESTART);
        Delay_100ms();
        hal_i2cRead(_slaveAddress, rReg, 2, END_MODE_STOP);

        tempData = rReg[0];        // MSB
        tempData <<= 8;
        tempData = tempData | rReg[1]; // LSB
        temp = tempData / 65536.00;
        temp = temp * 165;
        temp = temp - 40.00;

        Delay_100ms();
    }
    return temp;
}
float temphum4_getHuminidy()
{
    uint8_t wReg[1];
    uint8_t rReg[2];
    volatile uint16_t humData;
    volatile float hum;
    wReg[0] = 0x01;

    if( hal_gpio_intGet() )
    {
        hal_i2cStart();
        hal_i2cWrite(_slaveAddress, wReg, 1, END_MODE_RESTART);
        Delay_100ms();
        hal_i2cRead(_slaveAddress, rReg, 2, END_MODE_STOP);

        humData = rReg[0];        // MSB
        humData <<= 8;
        humData = humData | rReg[1]; // LSB
        hum = humData / 65536.00;
        hum = hum * 100;

       Delay_100ms();
    }
    return hum;
}





/* -------------------------------------------------------------------------- */
/*
  __temphum4_driver.c

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