//!-------------------------------------------------------------------
//! Copyright (C) 2007-2012 PHYCHIPS
//!
//! @file	commontypes.h
//! @brief	Type (re)definition and macros
//! 
//! $Id: commontypes.h 1661 2012-07-06 10:18:09Z jsyi $
//!-------------------------------------------------------------------
//! History
//!-------------------------------------------------------------------
//! 2007/09/01	jsyi		initial release


#ifndef COMMONTYPES_H
#define COMMONTYPES_H







//!-------------------------------------------------------------------                 
//! Definitions
//!------------------------------------------------------------------- 

typedef signed char 		int8; 		//   	-128 to +127
typedef unsigned char 		uint8; 		//  	0 to 255
typedef signed short 		int16; 		// 	-32768 to +32767
typedef unsigned short 		uint16; 	// 	0 to 65535
typedef signed int 			int32;		// 	-2147483648 to +2147483647
typedef unsigned int 		uint32;		// 	0 to 4 294 967 295
typedef long long			int64;		// 	-9223372036854775808 to 92233720368547758070
typedef unsigned long long	uint64;		// 	0 to 18446744073709551615
typedef unsigned char		BOOL;

#if defined ( __CC_ARM   )
	#define	PACKED_S	__packed
	#define PACKED_E
#elif defined (  __GNUC__  )
	#define	PACKED_S
	#define PACKED_E	__attribute__ ((packed))
#endif


// Constants
#ifndef FALSE
#define FALSE   	(0==1)
#endif
#ifndef TRUE
#define TRUE    	(1==1)
#endif
#ifndef NULL
#define NULL    	((void*)0)
#endif


#define	ON			1
#define OFF			0
#define OK      	1
#define NOK     	0

#define ENABLE   	1
#define ENABLED  	1
#define DISABLED 	0
#define DISABLE  	0

#define BIT7_SET	(0x80)
#define BIT6_SET	(0x40)
#define BIT5_SET	(0x20)
#define BIT4_SET	(0x10)
#define BIT3_SET	(0x08)
#define BIT2_SET	(0x04)
#define BIT1_SET	(0x02)
#define BIT0_SET	(0x01)

#define BIT7_CLR	(0x00)
#define BIT6_CLR	(0x00)
#define BIT5_CLR	(0x00)
#define BIT4_CLR	(0x00)
#define BIT3_CLR	(0x00)
#define BIT2_CLR	(0x00)
#define BIT1_CLR	(0x00)
#define BIT0_CLR	(0x00)

#define BIT7		(0x80)
#define BIT6		(0x40)
#define BIT5		(0x20)
#define BIT4		(0x10)
#define BIT3		(0x08)
#define BIT2		(0x04)
#define BIT1		(0x02)
#define BIT0		(0x01)






//!-------------------------------------------------------------------                 
//! Macros
//!------------------------------------------------------------------- 


//little-big endian management

// U16/U32 endian handlers
#define	LITTLE_ENDIAN
#ifdef LITTLE_ENDIAN     // => 16bit: (LSB,MSB), 32bit: (LSW,MSW) or (LSB0,LSB1,LSB2,LSB3) or (MSB3,MSB2,MSB1,MSB0)
#define MSB(u16)        (((uint8* )&u16)[1])
#define LSB(u16)        (((uint8* )&u16)[0])
#define MSW(u32)        (((uint16*)&u32)[1])
#define LSW(u32)        (((uint16*)&u32)[0])
#define MSB0(u32)       (((uint8* )&u32)[3])
#define MSB1(u32)       (((uint8* )&u32)[2])
#define MSB2(u32)       (((uint8* )&u32)[1])
#define MSB3(u32)       (((uint8* )&u32)[0])
#define LSB0(u32)       MSB3(u32)
#define LSB1(u32)       MSB2(u32)
#define LSB2(u32)       MSB1(u32)
#define LSB3(u32)       MSB0(u32)
#else // BIG_ENDIAN         => 16bit: (MSB,LSB), 32bit: (MSW,LSW) or (LSB3,LSB2,LSB1,LSB0) or (MSB0,MSB1,MSB2,MSB3)
#define MSB(u16)        (((uint8* )&u16)[0])
#define LSB(u16)        (((uint8* )&u16)[1])
#define MSW(u32)        (((uint16*)&u32)[0])
#define LSW(u32)        (((uint16*)&u32)[1])
#define MSB0(u32)       (((uint8* )&u32)[0])
#define MSB1(u32)       (((uint8* )&u32)[1])
#define MSB2(u32)       (((uint8* )&u32)[2])
#define MSB3(u32)       (((uint8* )&u32)[3])
#define LSB0(u32)       MSB3(u32)
#define LSB1(u32)       MSB2(u32)
#define LSB2(u32)       MSB1(u32)
#define LSB3(u32)       MSB0(u32)
#endif

// Byte(Endian) Converters
#define BC16(b)                       	 	\
   (  ((uint16)(     (b) &   0xFF) << 8)	\
   |  (     ((uint16)(b) & 0xFF00) >> 8)  	\
   )
#define BC32(b)                             		\
   (  ((uint32)(     (b) &       0xFF) << 24)  		\
   |  ((uint32)((uint16)(b) &     0xFF00) <<  8)	\
   |  (     ((uint32)(b) &   0xFF0000) >>  8)  		\
   |  (     ((uint32)(b) & 0xFF000000) >> 24)  		\
   )

// Bit and bytes manipulations
#define EMI_TST_BIT(address,mask)   ((*( (volatile unsigned char *) address)) & mask)
#define EMI_SET_BIT(address,mask)   ((*( (volatile unsigned char *) address)) = ((*( (volatile unsigned char *) address)) | mask))
#define EMI_CLR_BIT(address,mask)   ((*( (volatile unsigned char *) address)) = ((*( (volatile unsigned char *) address)) & ~mask))
#define EMI_READ(address)  			(*( (volatile unsigned char *) (address)))
#define EMI_WRITE(address, val) 	(*( (volatile unsigned char *) (address))) = (val)

#define TO_U16(u8_msb, u8_lsb)		((uint16)    ( (u8_msb) << 8) ) | ( (uint16) (u8_lsb) )
#define TO_I16(u8_msb, u8_lsb)		((int16)    ( (u8_msb) << 8) ) | ( (int16) (u8_lsb) )

// Misc
#define MAX(a, b)            		( (a)>(b) ? (a) : (b) )
#define MIN(a, b)            		( (a)<(b) ? (a) : (b) )

#define	H4(a) 	(a & 0xF0)
#define	L4(a)	(a & 0x0F)

#define LIMIT( val, min, max )  		(MAX( MIN( (val), (max) ), (min) ))

#define HW_REG(base,offset) 			*((volatile unsigned int *)((base) + (offset)))

#define MASK_BITS(msb, lsb) 			(((1U << ((msb) - (lsb) + 1)) - 1) << (lsb))
#define EXTRACT_BITS(arg, msb, lsb) ((arg & MASK_BITS(msb, lsb)) >> (lsb))
#define INSERT_BITS(arg, msb, lsb, value) \
    ((arg) = ((arg) & ~MASK_BITS(msb, lsb)) | (((value) << (lsb)) & MASK_BITS(msb, lsb)))

#define EXTRACT_BIT(arg, bit) 			((arg >> (bit)) & 1)
#define INSERT_BIT(arg, bit, value) 	((value) ? ((arg) |= (1 << (bit))) : ((arg) &= ~(1 << (bit))))
#define SET_BIT(arg, bit)       		((arg) |= (1 << (bit)))
#define CLEAR_BIT(arg, bit)     		((arg) &= ~(1 << (bit)))
#define TEST_BIT(arg, bit) 				((arg) & (1 << (bit)))

#define MASK_FIELD(field)               MASK_BITS(field##_MSB, field##_LSB)
#define EXTRACT_FIELD(arg, field)       EXTRACT_BITS(arg, field##_MSB, field##_LSB)
#define INSERT_FIELD(arg, field, value) INSERT_BITS(arg, field##_MSB, field##_LSB, value)

#endif

