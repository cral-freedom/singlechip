#include "onewrite.h"
#include "delay.h"
#include "18B20.h"
#include "adc.h"
#include "stdlib.h"
#include "NTC.h"

extern unsigned char DS18B20_ID[8][8];//��⵽�Ĵ�����ID������

int onewrite_init(OneWritePtr *OWP)
{
	*OWP = (OneWritePtr)malloc(sizeof(OneWrite));
	if(OWP)
	{
		(*OWP)->sen_type = NON;
		(*OWP)->NTC_Val = 0;
		(*OWP)->num = 0;
		(*OWP)->temp = (float *)malloc(sizeof(float)*8);
		if((*OWP)->temp)
			return 1;
	}
	return 0;
}

//������ɨ�躯���������NTC�����ȡNTCֵ
SensorType sen_Scan(OneWritePtr *OWP) 
{	
	if(DS18B20_Answer_Check())
		return DS18B20;
	(*OWP)->NTC_Val = Get_Adc_Average(1,10);/**adcͨ��Ҫ�������ö�**/
	if((*OWP)->NTC_Val>3000)  //2.5V����ֵԼΪ3100
		return NON;   //NTCδ��
	else
		return NTC;
}

void search_task(OneWritePtr *OWP)
{
	u8 num=0;
	int16_t ntc_temp;
	while(1)
	{
		(*OWP)->sen_type = sen_Scan(OWP);
		switch((*OWP)->sen_type)
		{
			case NON:
				printf("No sensor\r\n");
				break;
			case NTC:
				ntc_temp = read_NTC1((*OWP)->NTC_Val);
				printf("ntc_temp*10 = %d",ntc_temp);
				break;
			case DS18B20:
				(*OWP)->num = DS18B20_Search_Rom();//��ȡ18b20����
				if((*OWP)->num > 0)
				{	
					printf("DS18B20_SensorNum:%d\r\n",(*OWP)->num);
					for(num=0;num<(*OWP)->num;num++)
					{
						(*OWP)->temp[num] = DS18B20_Get_Temp(num);//��ȡ�¶�
						printf("ID:%02x%02x%02x%02x%02x%02x%02x%02x Temp:%.2f\r\n",DS18B20_ID[num][0],DS18B20_ID[num][1],DS18B20_ID[num][2],DS18B20_ID[num][3],DS18B20_ID[num][4],DS18B20_ID[num][5],DS18B20_ID[num][6],DS18B20_ID[num][7],(*OWP)->temp[num]);
						printf("\r\n");
					}
				}
				break;
			default:
				break;
		}
		delay_ms(2000);
	}
}


