/*
 * SubSys_SDcardOps.h
 *
 *  Created on: Feb 28, 2024
 *      Author: yunus
 */

#ifndef INC_SUBSYS_SDCARDOPS_H_
#define INC_SUBSYS_SDCARDOPS_H_


#include "main.h"
#include "fatfs.h"
#include "stm32f4xx_hal.h"

/*To convert number value to string format*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


FRESULT SD_Mount(const TCHAR* SD_path,BYTE Mount_Op);
FRESULT SD_Create_Dir(const TCHAR* SD_Dir);
FRESULT SD_Write(const TCHAR* SD_FileName,char* SD_Buffer);
char* Value2String(float Val);

typedef struct{

float Pressure;
float VertSpeed;
float VertHeight;
float Temperature;
float Voltage;
float GPS_Altitude;
float GPS_Longitude;
float GPS_Latitude;

int PacketNO;
int StatusSeparation;

}SD_Datas_HandleTypeDef;

#endif /* INC_SUBSYS_SDCARDOPS_H_ */
