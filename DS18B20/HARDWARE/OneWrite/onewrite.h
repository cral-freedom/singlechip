#ifndef __ONEWRITE_H
#define __ONEWRITE_H

#include "stdio.h"

typedef enum
{
	NON,
	NTC,
	DS18B20	
}SensorType;

typedef struct OneWrite
{
	SensorType sen_type;
	int num;
	float *temp;	//onewrite�ϵ�18b20���¶�ֵ	
	unsigned int NTC_Val;//NTCֵ
}OneWrite,*OneWritePtr;

int onewrite_init(OneWritePtr *OWP);
SensorType sen_Scan(OneWritePtr *OWP);
void search_task(OneWritePtr *OWP);

#endif

