#include <SubSys_SDcardOps.h>
#include "stm32f4xx_hal.h"
FATFS FATFS_Ob; 	 /* File system object */
FIL Fil_Ob;   		 /* File object */
FRESULT SD_result;   /* File function return code */


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


FRESULT SD_Create_Dir(const TCHAR* SD_Dir){

	SD_result = f_mkdir(SD_Dir);

	if((SD_result != FR_OK)&&(SD_result != FR_EXIST)){
		/**
		 * Buzzer will be activated like biiip biip bip
		 */
		while(1);
	}
	else{
		return FR_OK;
	}

}


FRESULT SD_Write(const TCHAR* SD_FileName, char* SD_Buffer){

	SD_result = f_open(&Fil_Ob, SD_FileName, FA_CREATE_ALWAYS | FA_WRITE);

	if(SD_result != FR_OK){
		/**
		 * Send to ground station error message
	     */
		while(1);
	}

	UINT written;
	SD_result =  f_write(&Fil_Ob,SD_Buffer,strlen(SD_Buffer),&written);

	SD_result = f_close(&Fil_Ob);
	    if (SD_result != FR_OK){
	    	/**
	    	 * Send to ground station error message
	    	 */
	    	while(1);
	    }
/* Tekli dönüştürme ve yazdırma olayına odaklanacak*/
return FR_OK;
}


char* Value2String(float Val){
	//The maximum value for float value is 4,294,967,295. We have maximum 1+3+3+3 = 10Byte hold
	char Frame[10];

	//Put Val variable into the Frame variable as a string
	sprintf(Frame, "%.2f", Val);

	//Malloc function returns the starting address of the allocated memory.
	char* Str = (char*)malloc(strlen(Frame)+1);

	//Coppy the Frame value to the Str variable  that was setted enough space
	strcpy(Str, Frame);

	//Return the string
	return Str;

}

