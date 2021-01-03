
#include "boot.h"
#include "video.h"
#include "memory_layout.h"
#include "encoder.h"

extern int usedVideoMode;

int NiceMenu(char **alts, int nAlts){
	int cur = 0, change = 1;
	int nTempCursorY = VIDEO_CURSOR_POSY;
	int nTempCursorX = VIDEO_CURSOR_POSX;

	while(1)
	{
		USBGetEvents();
		
		if (cur > 0 && risefall_xpad_BUTTON(TRIGGER_XPAD_PAD_UP) == 1) {
			cur--;
			change++;
		}

		if (cur < nAlts - 1 && risefall_xpad_BUTTON(TRIGGER_XPAD_PAD_DOWN) == 1) {
			cur++;
			change++;
		}

		if (risefall_xpad_BUTTON(TRIGGER_XPAD_KEY_A) == 1) {
			BootVideoClearScreen(&jpegBackdrop, nTempCursorY, VIDEO_CURSOR_POSY+1);
			VIDEO_CURSOR_POSY=nTempCursorY;
			VIDEO_CURSOR_POSX=nTempCursorX;
			return cur;
		}

		if (change) {
			int i;

			BootVideoClearScreen(&jpegBackdrop, nTempCursorY, VIDEO_CURSOR_POSY+1);
			VIDEO_CURSOR_POSY=nTempCursorY;

			for (i = cur - 5; i < cur + 5; i++) {
				if (video_encoder == ENCODER_XCALIBUR)
					VIDEO_CURSOR_POSX=250;
				else
					VIDEO_CURSOR_POSX=210;
				/*  this breaks the color changes below.... relative changes work, but not assignments
				// fix for huge resolutions
				if ( usedVideoMode == 4 )
						VIDEO_CURSOR_POSX+=100;
				else if ( usedVideoMode == 3 )
						VIDEO_CURSOR_POSX+=80;
				*/
				VIDEO_ATTR=0xffd8d800;
				if (i == cur)
					VIDEO_ATTR=0xffd8d8d8;
				if (i >= 0 && i < nAlts)
					printk (alts[i]);
				printk ("\n");
			}
		}

		change=0;	    
	}

}
