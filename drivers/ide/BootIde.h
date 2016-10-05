#ifndef __BOOT_IDE_H
#define __BOOT_IDE_H

/* Cromwell IDE driver code - GNU GPL */
tsHarddiskInfo tsaHarddiskInfo[2];  // static struct stores data about attached drives

typedef enum {
	IDE_CMD_NOOP = 0,
	IDE_CMD_RECALIBRATE = 0x10,
	IDE_CMD_READ_MULTI_RETRY = 0x20,
	IDE_CMD_READ_MULTI = IDE_CMD_READ_MULTI_RETRY,
	IDE_CMD_READ_MULTI_NORETRY = 0x21,
	
	IDE_CMD_READ_EXT = 0x24, /* 48-bit LBA */
    	
    	IDE_CMD_WRITE_MULTI_RETRY = 0x30,
    	
	IDE_CMD_DRIVE_DIAG = 0x90,
	IDE_CMD_SET_PARAMS = 0x91,
	IDE_CMD_STANDBY_IMMEDIATE = 0x94, /* 2 byte command- also send
	                                     IDE_CMD_STANDBY_IMMEDIATE2 */
	IDE_CMD_SET_MULTIMODE = 0xC6,
	IDE_CMD_STANDBY_IMMEDIATE2 = 0xE0,
	
	//Get info commands
	IDE_CMD_IDENTIFY = 0xEC,
	IDE_CMD_PACKET_IDENTIFY = 0xA1,
		
	ATAPI_SOFT_RESET = 0x08,
	
	IDE_CMD_SET_FEATURES = 0xEF,

	IDE_CMD_ATAPI_PACKET = 0xA0,

	//IDE security commands
	IDE_CMD_SECURITY_SET_PASSWORD = 0xF1,
	IDE_CMD_SECURITY_UNLOCK = 0xF2,
	IDE_CMD_SECURITY_DISABLE = 0xF6	
} ide_command_t;

typedef struct {
	unsigned char m_bPrecomp;
	unsigned char m_bCountSector;
	unsigned char m_bSector;
	unsigned short m_wCylinder;
	unsigned char m_bDrivehead;
	
	   /* 48-bit LBA */   
	unsigned char m_bCountSectorExt;   
	unsigned char m_bSectorExt;   
	unsigned short m_wCylinderExt; 
	
#       define IDE_DH_DEFAULT (0xA0)
#       define IDE_DH_HEAD(x) ((x) & 0x0F)
#       define IDE_DH_MASTER  (0x00)
#       define IDE_DH_SLAVE   (0x10)
#       define IDE_DH_DRIVE(x) ((((x) & 1) != 0)?IDE_DH_SLAVE:IDE_DH_MASTER)
#       define IDE_DH_LBA     (0x40)
#       define IDE_DH_CHS     (0x00)

} tsIdeCommandParams;

#define IDE_DEFAULT_COMMAND { 0xFFu, 0x01, 0x00, 0x0000, IDE_DH_DEFAULT | IDE_DH_SLAVE }



//Methods
int BootIdeInit(void);
int BootIdeReadSector(int nDriveIndex, void * pbBuffer, unsigned int block, int byte_offset, int n_bytes) ;
int BootIdeReadData(unsigned uIoBase, void * buf, size_t size);

#endif
