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
#include <stdbool.h>

#define LineSize 120 /*SD_Datas_HandleTypeDef struct's total byte*/


FRESULT SD_Mount(const TCHAR* SD_path,BYTE Mount_Op);
FRESULT SD_Create_Dir_File(const TCHAR* SD_Dir,const TCHAR* SD_FileName,char* SD_Buffer);

FRESULT SD_Write(char* SD_Buffer,const TCHAR* SD_FileName);
char* Value2String(float Val);
void SD_FillVariables(void);

typedef struct{

float Carr_Pressure;			/* Unit : pascal 		(11Byte) e.g => "101325.12" */
float Carr_VertSpeed;			/* Unit : meter/second	(6Byte) e.g  => "200.12" 	*/
float Carr_VertHeight;			/* Unit : meter 		(4Byte) e.g  => "223.4"		*/
float Carr_Temperature;			/* Unit : °celcius 		(5Byte) e.g  => "32.78"		*/

float Carr_Voltage;				/* Unit : Voltage 		(4Byte) e.g => "8.42"		*/

float Carr_GPS_Latitude;		/* Unit : meter		  (10Byte) e.g => "57.912109" -90° to +90°    */
float Carr_GPS_Longitude;		/* Unit : degrees (°) (10Byte) e.g => "78.0203478" -90° to +90°	   */
float Carr_GPS_Altitude;		/* Unit : degrees (°) (10Byte) e.g => "30.1585941" 0m to 9000meter */

uint16_t Carr_PacketNO;				/* Unit : Number (2Byte) e.g => "1265"  */
_Bool    Carr_StatusSeparation;		/* Unit : Number (1Byte) e.g => "1" 	*/
char* 	 Carr_SuccesSepInf;			/* Unit : String (22Byte) e.g ==> "Departure successful" or "Departure unsuccessful" */

}SD_Datas_HandleTypeDef;

#endif /* INC_SUBSYS_SDCARDOPS_H_ */
