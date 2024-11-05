/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

#include "Mcu.h"
#include "Port.h"
#include "Dio.h"

void TestDelay(uint32 delay)
{
   static volatile uint32 DelayTimer = 0;
   while(DelayTimer<delay)
   {
       DelayTimer++;
   }
   DelayTimer=0;
}

int main(void)
{
	/* Initialize the Mcu driver */
	Mcu_Init(&McuModuleConfiguration);
	Mcu_InitClock(McuClockSettingConfig_0);
#if (MCU_NO_PLL == STD_OFF)
	while ( MCU_PLL_LOCKED != Mcu_GetPllStatus() )
	{
		/* Busy wait until the System PLL is locked */
	}

	Mcu_DistributePllClock();
#endif
	Mcu_SetMode(McuModeSettingConf_0);

	/* Initialize all pins using the Port driver */
	Port_Init(&PortConfigSet);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED_RED, STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED_GREEN, STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED_BLUE, STD_HIGH);

    while(1)
    {
    	/* Get input level of channels */
#if 1
    	Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED_RED, STD_LOW);
		TestDelay(100000);
		Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED_RED, STD_HIGH);
		TestDelay(100000);
		Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED_GREEN, STD_LOW);
		TestDelay(100000);
		Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED_GREEN, STD_HIGH);
		TestDelay(100000);
		Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED_BLUE, STD_LOW);
		TestDelay(100000);
		Dio_WriteChannel(DioConf_DioChannel_DioChannel_LED_BLUE, STD_HIGH);
		TestDelay(100000);
#else
		Dio_FlipChannel(DioConf_DioChannel_DioChannel_LED_RED);
		TestDelay(100000);
		Dio_FlipChannel(DioConf_DioChannel_DioChannel_LED_RED);
		TestDelay(100000);
		Dio_FlipChannel(DioConf_DioChannel_DioChannel_LED_GREEN);
		TestDelay(100000);
		Dio_FlipChannel(DioConf_DioChannel_DioChannel_LED_GREEN);
		TestDelay(100000);
		Dio_FlipChannel(DioConf_DioChannel_DioChannel_LED_BLUE);
		TestDelay(100000);
		Dio_FlipChannel(DioConf_DioChannel_DioChannel_LED_BLUE);
		TestDelay(100000);
#endif
    }

    return 0;
}
