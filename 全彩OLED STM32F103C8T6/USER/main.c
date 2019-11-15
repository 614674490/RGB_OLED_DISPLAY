#include "oled.h"
#include "ssd1331.h"
#include "delay.h"
#include "bank.h"
#include "led.h"
#include "color.h"
int main()
{
	LED_Init();
	delay_init();
	OLED_Init();
	Clock_Test();
	while(1)
  {
		LED_Check();
	}		
}











