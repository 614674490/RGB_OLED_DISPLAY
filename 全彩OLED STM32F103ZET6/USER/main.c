#include "sys.h"
#include "led.h"
#include "W25Q64.h"
#include "string.h"
#include "oled_display.h"
int main(void)
{
	LED_Init();
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	OLED_Init();
	Clock_Test();
	while(1)
  {
		delay_ms(1000);
		LED_TOGGLE(LED0);
	}		
}
