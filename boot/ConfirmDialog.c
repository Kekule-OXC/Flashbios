/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "ConfirmDialog.h"
#include "boot.h"
#include "video.h"
//#include "cromwell.h"
#include "string.h"
//#include "lib/LPCMod/xblastDebug.h"
//#include "lib/cromwell/cromSystem.h"
#include "cromwell_types.h"
#include "encoder.h"

#define ComparebufSize 100
char bypassConfirmDialog[ComparebufSize];        //Arbitrary length
extern int usedVideoMode;
extern int usedAvType;

bool ConfirmDialog(const char * string, bool critical)
{
    //unsigned int yPos = 120;
    unsigned int stringLength = strlen(string);
    bool result = true;         //True = cancel.
    int nTempCursorY = VIDEO_CURSOR_POSY;
	int nTempCursorX = VIDEO_CURSOR_POSX;
        
    stringLength = stringLength > ComparebufSize ? ComparebufSize : stringLength;
    if(strncmp(string, bypassConfirmDialog, stringLength) == false && critical == false)
    {
        return false;
    }

    //BootVideoClearScreen(&jpegBackdrop, 0, 0xffff);
    BootVideoClearScreen(&jpegBackdrop, nTempCursorY, VIDEO_CURSOR_POSY+1);
			VIDEO_CURSOR_POSY=nTempCursorY;
			VIDEO_CURSOR_POSX=nTempCursorX;
    if (video_encoder == ENCODER_XCALIBUR)
		VIDEO_CURSOR_POSX=250;
		else
		VIDEO_CURSOR_POSX=210;
				
		
	// fix for huge resolutions for AV_SDTV modes
	if ( usedVideoMode == 4 ) //VIDEO_MODE_1024x576
		VIDEO_CURSOR_POSX+=100;//
	    else if ( usedVideoMode == 3 ) //VIDEO_MODE_800x600
		VIDEO_CURSOR_POSX+=80;

    VIDEO_ATTR=0xffff1515;                        //Red characters.
   // yPos = 100;//centerScreenPrintk(yPos, 
    printk("\n\n\2%s\n\n", string);
    VIDEO_ATTR=0xffffff;                //Back to white
    //yPos = 100;//centerScreenPrintk(yPos, 
    printk("Press Black to confirm\n");
    //centerScreenPrintk(yPos, 
    printk("Press White to cancel");
    
    while(1)
    {
        USBGetEvents();

        if(risefall_xpad_BUTTON(TRIGGER_XPAD_KEY_BLACK)==1)
        {//accept
       //     XBlastLogger(DEBUG_GENERAL_UI, DBG_LVL_DEBUG, "All correct buttons pressed. Accepting.");
       //     strncpy(bypassConfirmDialog, string, stringLength);
            //printk("start pressed");
            result = false;
            break;
        }

        if(risefall_xpad_BUTTON(TRIGGER_XPAD_KEY_WHITE) == 1)
        {//cancel
            //printk("back pressed");
            break;
        }
    }
    //BootVideoClearScreen(&jpegBackdrop, 0, 0xffff);
    BootVideoClearScreen(&jpegBackdrop, nTempCursorY, 0xffff);//VIDEO_CURSOR_POSY+1);
			VIDEO_CURSOR_POSY=nTempCursorY;
			VIDEO_CURSOR_POSX=nTempCursorX;
    
    return result;
}
