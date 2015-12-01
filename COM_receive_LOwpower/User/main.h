#ifndef _MAIN_H
#define _MAIN_H
#include "lpc11xx.h"
#include "string.h"
#include "stdio.h"
#include "queue.h"
#include "event.h"
#include "uart.h"
#include "ctrl.h"
#include "led.h"
#include "adc.h"

enum IAP2PacketEnums
{
    /* Start of packet bytes */
    kIAP2PacketSYNC        = 0xFF,
    kIAP2PacketSOP         = 0x5A,
    kIAP2PacketSOPOrig     = 0x55,

    kIAP2PacketSOPLen      = 2,

    kiAP2PacketVersion     = 1,

    /* Packet field index */
    kIAP2PacketIndexSYNC   = 0,   /* Start of packet byte 1 */
    kIAP2PacketIndexSOP    = 1,   /* Start of packet byte 2 */
    kIAP2PacketIndexLEN1   = 2,   /* Packet length MSB */
    kIAP2PacketIndexLEN2   = 3,   /* Packet length LSB */
    kIAP2PacketIndexCTRL   = 4,   /* Control flags */
    kIAP2PacketIndexSEQ    = 5,   /* SEQ number */
    kIAP2PacketIndexACK    = 6,   /* ACK number */
    kIAP2PacketIndexSESSID = 7,   /* Session ID */
    kIAP2PacketIndexCHK    = 8,   /* Header checksum */

    /* iAP 1.0/2.0 packet detect: FF 55 02 00 EE 10 */
    kIAP2PacketDetectLEN    = 0x0200,
    kIAP2PacketDetectCTRL   = 0xEE,
    kIAP2PacketDetectSEQ    = 0x10,

    /* iAP 1.0/2.0 packet detect BAD ACK: FF 55 04 00 02 04 EE 08 */
    kIAP2PacketDetectNACKLEN    = 0x0400,
    kIAP2PacketDetectNACKCTRL   = 0x02,
    kIAP2PacketDetectNACKSEQ    = 0x04,
    kIAP2PacketDetectNACKACK    = 0xEE,
    kIAP2PacketDetectNACKSESSID = 0x08,

    /*
    ** Packet Header Len
    ** SOP(2) + LEN(2) + CONTROL(1) + SEQ(1) + ACK(1) + SESSID(1) + CHK(1)
    */
    kIAP2PacketHeaderLen = 9,
    kIAP2PacketChksumLen = 1,   /* checksum byte length */

    //kiAP2PacketLenMax = 0xFFFF,
		kiAP2PacketLenMax =0x1000,       /*   最大的 payData改为1500个了 */
    kiAP2PacketMaxPayloadSize = (kiAP2PacketLenMax - kIAP2PacketHeaderLen - kIAP2PacketChksumLen),

    /* BitMask defines for bits in control byte */
    kIAP2PacketControlMaskSYN = 0x80,   /* synchronization */
    kIAP2PacketControlMaskACK = 0x40,   /* acknowledgement */
    kIAP2PacketControlMaskEAK = 0x20,   /* extended acknowledgement */
    kIAP2PacketControlMaskRST = 0x10,   /* reset */
    kIAP2PacketControlMaskSUS = 0x08,   /* suspend (sleep) */

    kIAP2PacketSynDataIdxVersion           = 0,
    kIAP2PacketSynDataIdxMaxOutstanding    = 1,
    kIAP2PacketSynDataIdxMaxPacketSize     = 2,
    kIAP2PacketSynDataIdxRetransmitTimeout = 4,
    kIAP2PacketSynDataIdxCumAckTimeout     = 6,
    kIAP2PacketSynDataIdxMaxRetransmit     = 8,
    kIAP2PacketSynDataIdxMaxCumACK         = 9,

    kIAP2PacketSynDataBaseLen              = 10,

    kIAP2PacketSynDataIdxSessionInfo       = 10,

    kIAP2PacketSynSessionIdxID             = 0,
    kIAP2PacketSynSessionIdxType           = 1,
    kIAP2PacketSynSessionIdxVersion        = 2,
    kIAP2PacketSynSessionSize              = 3,

    /* Session ID 0x0 shall not be used for any session types */
    kIAP2PacketReservedSessionID           = 0,

    kIAP2PacketMaxSessions                 = 10,

    kIAP2PacketSynOptionMaskLP             = 0x80,
    kIAP2PacketSynOptionMaskHP             = 0x40
};

typedef struct {
	unsigned char front;
	unsigned char rear;
	unsigned char rf_que[250];
} rf_data_str;

struct sysbit{
	uint8_t SYN:1;
	uint8_t ACK:1;
	uint8_t EAK:1;
	uint8_t RST:1;
	uint8_t SUS:1;
	uint8_t RFU:4;
	
}packbit;
typedef struct {
	  uint8_t sop1;   /* 0xFF */
    uint8_t sop2;   /* 0x5A */
    uint8_t len1;
    uint8_t len2;
    uint8_t ctl;
    uint8_t seq;
    uint8_t ack;
    uint8_t sess;
    uint8_t chk;

    uint8_t data [kiAP2PacketMaxPayloadSize];
    uint8_t datachk;
}iap2pack;




extern rf_data_str BC_DATA;
extern rf_data_str IP_DATA;



#endif


