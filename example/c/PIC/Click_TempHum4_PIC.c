/*
Example for TempHum4 Click

    Date          : Jan 2018.
    Author        : MikroE Team

Test configuration PIC :
    
    MCU             : P18F87K22
    Dev. Board      : EasyPIC PRO v7
    PIC Compiler ver : v7.1.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module and CS pin,RST pin as OUTPUT and INT pin as INPUT
- Application Initialization - Initializes Driver init and settings chip mode ACTIVE and configuration measurement
- Application Task - (code snippet) -  Reads the temperature and huminidy and logs to the USBUART every 500 ms.

*/

#include "Click_TempHum4_types.h"
#include "Click_TempHum4_config.h"

char temp_txt[256];
char hum_txt[256];
float  Temperature = 0;
float  Huminidy = 0;

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_i2cInit( _MIKROBUS1, &_TEMPHUM4_I2C_CFG[0] );
    mikrobus_logInit( _LOG_USBUART, 9600 );
    Delay_ms( 100 );
}

void applicationInit()
{
    temphum4_i2cDriverInit( (T_TEMPHUM4_P)&_MIKROBUS1_GPIO, (T_TEMPHUM4_P)&_MIKROBUS1_I2C, 0x42 );
    temphum4_setMode(_TEMPHUM4_MODE_ACTIVE);
    temphum4_Configuration(_TEMPHUM4_CONF_NORMAL_OPERATION |
                           _TEMPHUM4_CONF_HEATER_DISABLED |
                           _TEMPHUM4_CONF_MODE_TEMP_AND_HUM |
                           _TEMPHUM4_CONF_BATTERY_VOLTAGE_2_8_V |
                           _TEMPHUM4_CONF_TEMPERATURE_14bit |
                           _TEMPHUM4_CONF_HUMINIDY_14bit );
    Delay_100ms();
    mikrobus_logWrite("--- Init done ---",_LOG_LINE);
}

void applicationTask()
{
    Temperature = temphum4_getTemperature();
    Huminidy = temphum4_getHuminidy();
    FloatToStr(Temperature,temp_txt);
    mikrobus_logWrite("Temperature : ",_LOG_TEXT);
    mikrobus_logWrite(temp_txt,_LOG_LINE);
    FloatToStr(Huminidy,hum_txt);
    mikrobus_logWrite("Huminidy : ",_LOG_TEXT);
    mikrobus_logWrite(hum_txt,_LOG_LINE);
    Delay_ms( 500 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}