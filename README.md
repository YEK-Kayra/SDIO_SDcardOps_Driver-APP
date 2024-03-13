# SDCARD
** SD CARD SCHEMATIC & FIRST SIGHT INFORMATION **


![image](https://github.com/nilsuhyt/SDCARD/assets/158216829/3aba63a9-7a23-4853-b812-2770a7ff7061)
> [!NOTE]
> SDIO interface is different SPI interface. You can not program SD card module by SDIO if you have. So you have to design again on your board gives up. And one important thing is that your stm32 mcu has to contain SDIO unit otherwise you  can not use this programming method
> 
> 1.After the design the first step is setting CUBEMX in stm32cubeide
>
> 2.Enter the pinout & configuration and select the connectivity click SDIO
> 
> 3.SDIO global interrupt will be enabled in the NVIC Settings
> 
> 4.SDIO DMA Settings will be activated. There will be DMA_TX and DMA_RX like as given below if you dont have you have to create two of them by using Add button.

> [!TIP]
> Choose sd card and sets MAX_SS and MIN_SS  as given up
And next page enabled “use dma template” at Advanced Setting.
> 
> ![image](https://github.com/nilsuhyt/SDCARD/assets/158216829/7f5b085d-cd2b-46d7-acfa-e54cbacc7f97)
> 
> ![image](https://github.com/nilsuhyt/SDCARD/assets/158216829/e8ef2024-f151-4bc7-afbc-a45cf55fc249)
> 
> ![image](https://github.com/nilsuhyt/SDCARD/assets/158216829/7b1a33cb-747f-43a0-8772-4d334b2c6510)

> [!WARNING]
> **SOME BUGS**:
> If I choose SD 4 bits Wide Bus in smt32cube’s cubemx. You can not create directory on the sd card. And the program is stucking.
Your design is according to the SD 4 bits Wide Bus but the problem is going on , 
![image](https://github.com/nilsuhyt/SDCARD/assets/158216829/238dd6b1-9515-4edd-b27b-7aac5f045fac)
>
> 1. Change the hsd.Init.BusWide = SDIO_BUS_WIDE_1B otherwise you can not work with your sd card. İf you did you’ll see sd card is working
>    **OR**
> 2. Select SD 1 bit and don’t waste your time with bugs. But your SD 4 bits Wide Bus design will be changed a little bit like decrease 3 data bit pin. But that’s not a problem . the card will be working









