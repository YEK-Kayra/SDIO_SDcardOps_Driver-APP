
/******************************************************************************
         			#### SD CARD OPERATIONS INCLUDES ####
******************************************************************************/
#include <SubSys_SDcardOps.h>
#include "stm32f4xx_hal.h"


/******************************************************************************
         			#### SD CARD OPERATIONS STRUCTURES ####
******************************************************************************/
/* LIBRARY VARIABLES OF "ff.h" AND "FatFs.h" */
FATFS FATFS_Ob; 	 /* File system object */
FIL FilePage;   	 /* SD card page that is stored in the directory */
FRESULT SD_result;   /* File function return code */

/* SD CARD TOP FRAME */
char* DataTopFrame = "PacketNO, GPS_Latitude, GPS_Longitude, GPS_Altitude, Pressure, VertSpeed, VertHeight, Temperature, Voltage, StatusSeparation, SuccesSepInf";

/* We create an object that keeps different satellite variable */
SD_Datas_HandleTypeDef SD_Data;

//We create a buffer that contains satellite's carrier variables. We fill it by SD_Data objects variables
char* SdDatasBuf[LineSize];



void SD_FillVariables(void){

    	SD_Data.Carr_Pressure = 101325.12;  // there will be "MS5611_Press" instead of "101325.12"
    	SD_Data.Carr_Temperature = 32.78;
    	SD_Data.Carr_VertHeight = 1500.45;
    	SD_Data.Carr_VertSpeed = 200.44;

    	SD_Data.Carr_GPS_Latitude = 89.912109;
    	SD_Data.Carr_GPS_Longitude = 89.0203478;
    	SD_Data.Carr_GPS_Altitude = 3000.1585941;

    	SD_Data.Carr_Voltage = 8.42;
    	SD_Data.Carr_PacketNO = 1256;
    	SD_Data.Carr_StatusSeparation = 1;
    	SD_Data.Carr_SuccesSepInf = "Departure unsuccessful";

    	sprintf(SdDatasBuf,"<%d, %.4f, %.4f, %.4f, %.2f, %.2f, %.2f, %.2f, %.2f, %d, %s >\n",
    	    				  	  	  	  	  	  	  	  	  	  	SD_Data.Carr_PacketNO,SD_Data.Carr_GPS_Latitude,SD_Data.Carr_GPS_Longitude,
    	    														SD_Data.Carr_GPS_Altitude,SD_Data.Carr_Pressure,SD_Data.Carr_Temperature,
    	    		  												SD_Data.Carr_VertHeight,SD_Data.Carr_VertSpeed,SD_Data.Carr_Voltage,
    	    		  												SD_Data.Carr_StatusSeparation,SD_Data.Carr_SuccesSepInf);

}


FRESULT SD_Mount (const TCHAR* SD_path, BYTE Mount_Op)
{

	SD_result = f_mount(&FATFS_Ob, SD_path, Mount_Op);

	if(SD_result != FR_OK){
		/**
		 * Buzzer will be activated like biiip biip bip
		 */
		while(1);
	}
	else{

		return FR_OK;

	}
}


FRESULT SD_Create_Dir_File(const TCHAR* SD_Dir,const TCHAR* SD_FileName,char* SD_Buffer){

	SD_result = f_mkdir(SD_Dir);

	if((SD_result != FR_OK)&&(SD_result != FR_EXIST)){
		/**
		 * Buzzer will be activated like biiip biip bip
		 */
		while(1);
	}
	else{

		SD_result = f_open(&FilePage, SD_FileName, FA_CREATE_ALWAYS | FA_WRITE);
		SD_result = f_close(&FilePage);

		sprintf(SD_Buffer,"%s\n",DataTopFrame);
		SD_Write(SD_Buffer,"SAT_CAR/STM32.TXT");

		if(SD_result != FR_OK){
				/**
				 * Send to ground station error message
			     */
				while(1);
			}
		SD_result = f_close(&FilePage);
		return FR_OK;
	}

}


FRESULT SD_Write(char* SD_Buffer,const TCHAR* SD_FileName){

	UINT written;

	SD_result = f_open(&FilePage, SD_FileName, FA_OPEN_APPEND | FA_WRITE);

	SD_result =  f_write(&FilePage,SD_Buffer,strlen(SD_Buffer),&written);

	SD_result = f_close(&FilePage);

	return FR_OK;
}
