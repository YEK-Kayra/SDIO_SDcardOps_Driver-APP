#include <SubSys_SDcardOps.h>
#include "stm32f4xx_hal.h"
FATFS FATFS_Ob; 	 /* File system object */
FIL FilePage;   	 /* SD card page that is stored in the directory */
FRESULT SD_result;   /* File function return code */
char* DataTopFrame = "PacketNO, GPS_Latitude, GPS_Longitude, GPS_Altitude, Pressure, VertSpeed, VertHeight, Temperature, Voltage, StatusSeparation, SuccesSepInf";

extern char SdDatasBuf[LineSize];
// INIT FONKSİYONUNU DAHİL EDİNCE STRUCT TANIMLAMALARINI DAHHA İYİ YAPICAZ 1-2 GÜNE


/**
 * @brief
 * FatFs kullanarak bir mikro SD kartı temsil etmek için bir mantıksal sürücü oluşturabilir ve bu sürücü üzerinde dosya sistemine erişebilirsiniz.
 * FatFs bir modüldür. SD kartı doğrudan bilmediği için onun temsilini programlar ve düşük seviye kütüphaneler ile gerçek sd karta iletilir (Resim 1.0)


FatFs requires work area (filesystem object) for each logical drives (FAT volumes). Prior to perform any file/directory operations,
a filesystem object needs to be registered with f_mount function for the logical drive.
The file/directory API functions get ready to work after this procedure.


 * 		       SD card is an identified logic driver from PC. And pc give a logic driver name to your SD card like "E:"
 * 			   And your PC,STM's MCU... use this logic driver
 * @param[IN]  SD_path is Logical drive number. It can be "E:\","e/" , "\", "1:" etc.
 * 		   	   Check your SD card's name that is given from the PC
 */
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


FRESULT SD_Create_Dir_File(const TCHAR* SD_Dir,const TCHAR* SD_FileName){

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

		//sprintf(SdDatas,"%s\n",DataTopFrame);
		//SD_Write(SdDatas,"SAT_CAR/STM32.TXT");

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


//f_lseek(&FilePage, f_size(&FilePage));

FRESULT SD_Write(char* SD_Buffer,const TCHAR* SD_FileName){

	UINT written;

	SD_result = f_open(&FilePage, SD_FileName, FA_OPEN_APPEND | FA_WRITE);





	SD_result =  f_write(&FilePage,SD_Buffer,strlen(SD_Buffer),&written);

	SD_result = f_close(&FilePage);

	return FR_OK;
}


/**
 * This function returns start address of the data block. So it is had to be defined " char* "
 */
char* Value2String(float Val){

//The maximum value for float value is 4,294,967,295. We have maximum 1+3+3+3 = 10Byte hold
	char Frame[10];

	//Put Val variable into the Frame variable as a string
	//int sprintf(char *buffer, const char *format) ==> Frame and Val are addresses
	sprintf(Frame, "%.2f", Val);
	//Malloc function returns the starting address of the allocated memory.
	char* Str = (char*)malloc(strlen(Frame)+1);

	//Coppy the Frame value to the Str variable  that was setted enough space
	//char* strcpy(char *dest, const char *src) ==>  Str and Frame are addresses.
	strcpy(Str, Frame);

	//Return the string
	return Str;

}

