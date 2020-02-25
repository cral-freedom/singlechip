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
	float *temp;	//onewrite上的18b20的温度值	
	unsigned int NTC_Val;//NTC值
}OneWrite,*OneWritePtr;

int onewrite_init(OneWritePtr *OWP);
SensorType sen_Scan(OneWritePtr *OWP);
void search_task(OneWritePtr *OWP);

#endif

