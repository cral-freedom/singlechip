#include "stm32f10x.h"
#include "stdio.h"
#include "usart.h"
#include "18B20.h"
#include "adc.h"
#include "onewrite.h"

int main(void)
{
	OneWritePtr OWP;
	uart_init(9600);
	if(onewrite_init(&OWP)) 
	{
		Adc_Init();
		DS18B20_GPIO_Config();
		DS18B20_Rst();
//		while(DS18B20_Init())//初始化DS18B20,兼检测18B20
//		{
//			printf("DS18B20 Check Failed!\r\n");  
//		}
//		printf("DS18B20 Ready!\r\n");
		search_task(&OWP);
	}
		
		
}
