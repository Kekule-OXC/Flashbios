/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

 /* 2003-01-07  andy@warmcat.com  Created
 */

#include "boot.h"
#include "BootFlash.h"
#include "memory_layout.h"

const KNOWN_FLASH_TYPE aknownflashtypesDefault[] = {
	{ 0x01, 0xb0, "AMD_Am29F002BT/NBT", 0x40000 },
	{ 0x01, 0x34, "AMD_Am29F002BB/NBB", 0x40000 },
	{ 0x01, 0x51, "AMD_Am29F200BT", 0x40000 },
	{ 0x01, 0x57, "AMD_Am29F200BB", 0x40000 },
	{ 0x01, 0x40, "AMD_Am29LV002BT", 0x40000 },
	{ 0x01, 0xc2, "AMD_Am29LV002BB", 0x40000 },
	{ 0x01, 0x3b, "AMD_Am29LV200BT", 0x40000 },
	{ 0x01, 0xbf, "AMD_Am29LV200BB", 0x40000 },
	{ 0x01, 0x0c, "AMD_Am29DL400BT", 0x80000 },
	{ 0x01, 0x0f, "AMD_Am29DL400BB", 0x80000 },
	{ 0x01, 0x77, "AMD_Am29F004BT", 0x80000 },
	{ 0x01, 0x7b, "AMD_Am29F004BB", 0x80000 },
	{ 0x01, 0xa4, "AMD_Am29F040B", 0x80000 },
	{ 0x01, 0x23, "AMD_Am29F400BT", 0x80000 },
	{ 0x01, 0xab, "AMD_Am29F400BB", 0x80000 },
        { 0x01, 0xad, "XECUTER3", 0x200000 },
	{ 0x01, 0xb5, "AMD_Am29LV004BT", 0x80000 },
	{ 0x01, 0xb6, "AMD_Am29LV004BB", 0x80000 },
	{ 0x01, 0x4f, "AMD_Am29LV040B", 0x80000 },
	{ 0x01, 0xb9, "AMD_Am29LV400BT", 0x80000 },
	{ 0x01, 0xba, "AMD_Am29LV400BB", 0x80000 },
	{ 0x01, 0x4a, "AMD_Am29DL800BT", 0x100000 },
	{ 0x01, 0xcb, "AMD_Am29DL800BB", 0x100000 },
	{ 0x01, 0xd5, "AMD_Am29F080B", 0x100000 },
	{ 0x01, 0xd6, "AMD_Am29F800BT", 0x100000 },
	{ 0x01, 0x58, "AMD_Am29F800BB", 0x100000 },
	{ 0x01, 0x3e, "AMD_Am29LV008BT", 0x100000 },
	{ 0x01, 0x37, "AMD_Am29LV008BB", 0x100000 },
	{ 0x01, 0x38, "AMD_Am29LV080B", 0x100000 },
	{ 0x01, 0xda, "AMD_Am29LV800BT/DT", 0x100000 },
	{ 0x01, 0x5b, "AMD_Am29LV800BB/DB", 0x100000 },
	{ 0x37, 0x8c, "AMIC_A29002T/290021T", 0x40000 },
	{ 0x37, 0x0d, "AMIC_A29002U/290021U", 0x40000 },
	{ 0x37, 0x86, "AMIC_A29040A", 0x80000 },
	{ 0x37, 0xb0, "AMIC_A29400T/294001T", 0x80000 },
	{ 0x37, 0x31, "AMIC_A29400U/294001U", 0x80000 },
	{ 0x37, 0x34, "AMIC_A29L004T/A29L400T", 0x80000 },
	{ 0x37, 0xb5, "AMIC_A29L004U/A29L400U", 0x80000 },
	{ 0x37, 0x92, "AMIC_A29L040", 0x80000 },
	{ 0x37, 0x0e, "AMIC_A29800T", 0x100000 },
	{ 0x37, 0x8f, "AMIC_A29800U", 0x100000 },
	{ 0x37, 0x1a, "AMIC_A29L008T/A29L800T", 0x100000 },
	{ 0x37, 0x9b, "AMIC_A29L008U/A29L800U", 0x100000 },
	{ 0x04, 0xb0, "Fujitsu_MBM29F002TC", 0x40000 },
	{ 0x04, 0x34, "Fujitsu_MBM29F002BC", 0x40000 },
	{ 0x04, 0x51, "Fujitsu_MBM29F200TC", 0x40000 },
	{ 0x04, 0x57, "Fujitsu_MBM29F200BC", 0x40000 },
	{ 0x04, 0x40, "Fujitsu_MBM29LV002TC", 0x40000 },
	{ 0x04, 0xc2, "Fujitsu_MBM29LV002BC", 0x40000 },
	{ 0x04, 0x3b, "Fujitsu_MBM29LV200TC", 0x40000 },
	{ 0x04, 0xbf, "Fujitsu_MBM29LV200BC", 0x40000 },
	{ 0x04, 0x0c, "Fujitsu_MBM29DL400TC", 0x80000 },
	{ 0x04, 0x0f, "Fujitsu_MBM29DL400BC", 0x80000 },
	{ 0x04, 0x77, "Fujitsu_MBM29F004TC", 0x80000 },
	{ 0x04, 0x7b, "Fujitsu_MBM29F004BC", 0x80000 },
	{ 0x04, 0xa4, "Fujitsu_MBM29F040C", 0x80000 },
	{ 0x04, 0x23, "Fujitsu_MBM29F400TC", 0x80000 },
	{ 0x04, 0xab, "Fujitsu_MBM29F400BC", 0x80000 },
	{ 0x04, 0xb5, "Fujitsu_MBM29LV004TC", 0x80000 },
	{ 0x04, 0xb6, "Fujitsu_MBM29LV004BC", 0x80000 },
	{ 0x04, 0xb9, "Fujitsu_MBM29LV400TC", 0x80000 },
	{ 0x04, 0xba, "Fujitsu_MBM29LV400BC", 0x80000 },
	{ 0x04, 0x4a, "Fujitsu_MBM29DL800TA", 0x100000 },
	{ 0x04, 0xcb, "Fujitsu_MBM29DL800BA", 0x100000 },
	{ 0x04, 0xd5, "Fujitsu_MBM29F080A", 0x100000 },
	{ 0x04, 0xd6, "Fujitsu_MBM29F800TA", 0x100000 },
	{ 0x04, 0x58, "Fujitsu_MBM29F800BA", 0x100000 },
	{ 0x04, 0x3e, "Fujitsu_MBM29LV008TA", 0x100000 },
	{ 0x04, 0x37, "Fujitsu_MBM29LV008BA", 0x100000 },
	{ 0x04, 0x38, "Fujitsu_MBM29LV080A", 0x100000 },
	{ 0x04, 0xda, "Fujitsu_MBM29LV800TA/TE", 0x100000 },
	{ 0x04, 0x5b, "Fujitsu_MBM29LV800BA/BE", 0x100000 },
	{ 0xad, 0xb0, "Hynix_HY29F002", 0x40000 },
	{ 0xad, 0xa4, "Hynix_HY29F040A", 0x80000 },
	{ 0xad, 0x23, "Hynix_HY29F400T/AT", 0x80000 },
	{ 0xad, 0xab, "Hynix_HY29F400B/AB", 0x80000 },
	{ 0xad, 0xb9, "Hynix_HY29LV400T", 0x80000 },
	{ 0xad, 0xba, "Hynix_HY29LV400B", 0x80000 },
	{ 0xad, 0xd5, "Hynix_HY29F080", 0x100000 },
	{ 0xad, 0xd6, "Hynix_HY29F800T/AT", 0x100000 },
	{ 0xad, 0x58, "Hynix_HY29F800B/AB", 0x100000 },
	{ 0xad, 0xda, "Hynix_HY29LV800T", 0x100000 },
	{ 0xad, 0x5b, "Hynix_HY29LV800B", 0x100000 },
	{ 0xc2, 0xb0, "Macronix_MX29F002T/NT", 0x40000 },
	{ 0xc2, 0x34, "Macronix_MX29F002B/NB", 0x40000 },
	{ 0xc2, 0x36, "Macronix_MX29F022T/NT", 0x40000 },
	{ 0xc2, 0x37, "Macronix_MX29F022B/NB", 0x40000 },
	{ 0xc2, 0x51, "Macronix_MX29F200T", 0x40000 },
	{ 0xc2, 0x57, "Macronix_MX29F200B", 0x40000 },
	{ 0xc2, 0x45, "Macronix_MX29F004T", 0x80000 },
	{ 0xc2, 0x46, "Macronix_MX29F004B", 0x80000 },
	{ 0xc2, 0xa4, "Macronix_MX29F040", 0x80000 },
	{ 0xc2, 0x23, "Macronix_MX29F400T", 0x80000 },
	{ 0xc2, 0xab, "Macronix_MX29F400B", 0x80000 },
	{ 0xc2, 0xb5, "Macronix_MX29LV004T", 0x80000 },
	{ 0xc2, 0xb6, "Macronix_MX29LV004B", 0x80000 },
	{ 0xc2, 0x4f, "Macronix_MX29LV040", 0x80000 },
	{ 0xc2, 0xb9, "Macronix_MX29LV400T", 0x80000 },
	{ 0xc2, 0xba, "Macronix_MX29LV400B", 0x80000 },
	{ 0xc2, 0xd5, "Macronix_MX29F080", 0x100000 },
	{ 0xc2, 0xd6, "Macronix_MX29F800T", 0x100000 },
	{ 0xc2, 0x58, "Macronix_MX29F800B", 0x100000 },
	{ 0xc2, 0x3e, "Macronix_MX29LV008T", 0x100000 },
	{ 0xc2, 0x37, "Macronix_MX29LV008B", 0x100000 },
	{ 0xc2, 0x38, "Macronix_MX29LV081", 0x100000 },
	{ 0xc2, 0xda, "Macronix_MX29LV800T", 0x100000 },
	{ 0xc2, 0x5b, "Macronix_MX29LV800B", 0x100000 },
	{ 0xb0, 0xc9, "Sharp_LHF00L02/L06/L07", 0x100000 },
	{ 0xb0, 0xcf, "Sharp_LHF00L03/L04/L05", 0x100000 },
	{ 0x89, 0xa2, "Sharp_LH28F008SA_series", 0x100000 },
	{ 0x89, 0xa6, "Sharp_LH28F008SC_series", 0x100000 },
	{ 0xb0, 0xec, "Sharp_LH28F008BJxx-PT_series", 0x100000 },
	{ 0xb0, 0xed, "Sharp_LH28F008BJxx-PB_series", 0x100000 },
	{ 0xb0, 0x4b, "Sharp_LH28F800BVxx-BTL_series", 0x100000 },
	{ 0xb0, 0x4c, "Sharp_LH28F800BVxx-TV_series", 0x100000 },
	{ 0xb0, 0x4d, "Sharp_LH28F800BVxx-BV_series", 0x100000 },
	{ 0xbf, 0x10, "SST_29EE020", 0x40000 },
	{ 0xbf, 0x12, "SST_29LE020/29VE020", 0x40000 },
	{ 0xbf, 0xd6, "SST_39LF020/39VF020", 0x40000 },
	{ 0xbf, 0xb6, "SST_39SF020A", 0x40000 },
	{ 0xbf, 0x57, "SST_49LF002A", 0x40000 },
	{ 0xbf, 0x61, "SST_49LF020", 0x40000 },
	{ 0xbf, 0x52, "SST_49LF020A", 0x40000 },
	{ 0xbf, 0x1b, "SST_49LF003A", 0x60000 },
	{ 0xbf, 0x1c, "SST_49LF030A", 0x60000 },
	{ 0xbf, 0x13, "SST_29SF040", 0x80000 },
	{ 0xbf, 0x14, "SST_29VF040", 0x80000 },
	{ 0xbf, 0xd7, "SST_39LF040/39VF040", 0x80000 },
	{ 0xbf, 0xb7, "SST_39SF040", 0x80000 },
	{ 0xbf, 0x60, "SST_49LF004A/B", 0x80000 },
	{ 0xbf, 0x51, "SST_49LF040", 0x80000 },
	{ 0xbf, 0xd8, "SST_39LF080/39VF080/39VF088", 0x100000 },
	{ 0xbf, 0x5a, "SST_49LF008A", 0x100000 },
	{ 0xbf, 0x5b, "SST_49LF080A", 0x100000 },
	{ 0x20, 0xb0, "ST_M29F002T/NT/BT/BNT", 0x40000 },
	{ 0x20, 0x34, "ST_M29F002B/BB", 0x40000 },
	{ 0x20, 0xd3, "ST_M29F200BT", 0x40000 },
	{ 0x20, 0xd4, "ST_M29F200BB", 0x40000 },
	{ 0x20, 0xe2, "ST_M29F040_series", 0x80000 },
	{ 0x20, 0xd5, "ST_M29F400T/BT", 0x80000 },
	{ 0x20, 0xd6, "ST_M29F400B/BB", 0x80000 },
	{ 0x20, 0xf1, "ST_M29F080_series", 0x100000 },
	{ 0x20, 0xec, "ST_M29F800DT", 0x100000 },
	{ 0x20, 0x58, "ST_M29F800DB", 0x100000 },
	{ 0xda, 0x45, "Winbond_W29C020", 0x40000 },
	{ 0xda, 0xb5, "Winbond_W39L020", 0x40000 },
	{ 0xda, 0x0b, "Winbond_W49F002U", 0x40000 },
	{ 0xda, 0x8c, "Winbond_W49F020", 0x40000 },
	{ 0xda, 0xb0, "Winbond_W49V002A", 0x40000 },
	{ 0xda, 0x46, "Winbond_W29C040", 0x40000 },
	{ 0xda, 0xb6, "Winbond_W39L040", 0x80000 },
	{ 0xda, 0x3d, "Winbond_W39V040A", 0x80000 },
	{ 0, 0, "\0", 0 }
};


 // callback to show progress
void draw_box(int val, int max, unsigned long col);
void draw_box(int val, int max, unsigned long col){
        int x,y,l,w,h,m;
        DWORD *fb=(DWORD*)FRAMEBUFFER_START;

        if(max<2){
                return;
        }

        w=currentvideomodedetails.m_dwWidthInPixels;
        h=currentvideomodedetails.m_dwHeightInLines;
        l=w-100;
        y=h-100;
        m=((w-150)>>2)*val/max;
        m*=4;
        m+=50;
        for(x=50;x<l;x++){
                fb[y*w+x]=0xffffffff;
                fb[(y+1)*w+x]=0xffffffff;
                if(x>55 && x<m){
                        int z;
                        for(z=5;z<45;z++){
                                fb[(y+z)*w+x]=col;
                        }

                }
                fb[(y+50)*w+x]=0xffffffff;
                fb[(y+51)*w+x]=0xffffffff;
        }
        for(;y<h-50;y++){
                fb[y*w+51]=0xffffffff;
                fb[y*w+50]=0xffffffff;
                fb[y*w+l-1]=0xffffffff;
                fb[y*w+l-2]=0xffffffff;
        }



}

bool BootFlashUserInterface(void * pvoidObjectFlash, ENUM_EVENTS ee, DWORD dwPos, DWORD dwExtent) {
	if(ee==EE_ERASE_UPDATE){
		draw_box(dwPos,dwExtent,0xffffff00);
	}
	if(ee==EE_PROGRAM_UPDATE){
		draw_box(dwPos,dwExtent,0xff00ff00);
	}
	//return true;


	return true;
}


int BootReflashAndReset(BYTE *pbNewData, DWORD dwStartOffset, DWORD dwLength)
{
	OBJECT_FLASH of;
	bool fMore=true;

	
	// prep our flash object with start address and params
	of.m_pbMemoryMappedStartAddress=(BYTE *)LPCFlashadress;
	of.m_dwStartOffset=dwStartOffset;
	of.m_dwLengthUsedArea=dwLength;
	of.m_pcallbackFlash=BootFlashUserInterface;

	if(!BootFlashGetDescriptor(&of, (KNOWN_FLASH_TYPE *)&aknownflashtypesDefault[0])) {
		printk("Unknown flash! Halting\n");
		while(1);
	}

	VIDEO_ATTR=0xffc8c8c8;
	printk("Found Flash: ");
	VIDEO_ATTR=0xffc8c800;

	printk("%s (%02x %02x)\n",of.m_szFlashDescription,
	       of.m_bManufacturerId,of.m_bDeviceId);
	
	if(!of.m_fIsBelievedCapableOfWriteAndErase){
		printk("Flash writeprotected? Halting\n");
		while(1);
	}
	if(of.m_dwLengthInBytes<(dwStartOffset+dwLength)){
		printk("Flash to small for biosimage. Halting\n");
		while(1);
	}




	__asm__ __volatile__ ( "cli ");  // ISRs are in flash, no interrupts possible now until reset

	while(fMore) {
		printk("\n\n");
		printk("\2FLASHING MODCHIP...\n");
		printk("\2\n");
		VIDEO_ATTR=0xffc8c8c8;
		printk("WARNING!\n"
			   "PLEASE DO NOT TOUCH THE CONSOLE WHILST FLASHING IS IN PROGRESS!\n"
		       "YOUR CONSOLE SHOULD SHUTDOWN AUTOMATICALLY WHEN FLASHING IS\n"
			   "COMPLETED. IF YOUR CONSOLE DOES NOT TURN OFF PLEASE DO SO\n"
			   "MANUALLY WHEN THE POWER LED TURNS AMBER.\n");

		if(BootFlashEraseMinimalRegion(&of)) {
			if(BootFlashProgram(&of, pbNewData)) {
				fMore=false;  // good situation
			} else { // failed program
				printk("Programming failed: %s\n",of.m_szAdditionalErrorInfo);
				while(1);
			}
		} else { // failed erase
			printk("Erase failed\n");
			while(1);
		}
	}

	// okay, try to restart by cycling power


#define XBOX_SMB_IO_BASE 0xC000
#define XBOX_SMB_HOST_ADDRESS       (0x4 + XBOX_SMB_IO_BASE)
#define XBOX_SMB_HOST_COMMAND       (0x8 + XBOX_SMB_IO_BASE)
#define XBOX_SMB_HOST_DATA          (0x6 + XBOX_SMB_IO_BASE)
#define XBOX_SMB_GLOBAL_ENABLE      (0x2 + XBOX_SMB_IO_BASE)

#define XBOX_PIC_ADDRESS 0x10

#define SMC_CMD_POWER 0x02
#define SMC_SUBCMD_POWER_OFF 0x80

#define SMC_SUBCMD_POWER_RESET 0x01
	/* poweroff */

        IoOutputWord(XBOX_SMB_HOST_ADDRESS, ((XBOX_PIC_ADDRESS) << 1));
        IoOutputByte(XBOX_SMB_HOST_COMMAND, SMC_CMD_POWER);
        IoOutputWord(XBOX_SMB_HOST_DATA, SMC_SUBCMD_POWER_RESET);
        IoOutputWord(XBOX_SMB_IO_BASE, IoInputWord(XBOX_SMB_IO_BASE));
        IoOutputByte(XBOX_SMB_GLOBAL_ENABLE, 0x0a);

	while(1);

	return 0; // keep compiler happy
}

