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

FRESULT SD_Mount(const TCHAR* SD_path,BYTE Mount_Op);
FRESULT SD_Create_Dir(const TCHAR* Dir_Name);


#endif /* INC_SUBSYS_SDCARDOPS_H_ */
