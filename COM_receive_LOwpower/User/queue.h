#ifndef _QUEUE_H
#define _QUEUE_H

extern void queue_in_buf(unsigned char in);
extern unsigned char queue_out_buf(void);
extern void queue_in_buf1(unsigned char in);
extern unsigned char queue_out_buf1(void);
extern void queue_in_buf0(unsigned char in);
extern unsigned char queue_out_buf0(void);
extern void queue_bc_reset(void);

extern void queue_reset(void);

extern void App_in_cmd(unsigned char in,unsigned char opt);
extern void App_out_cmd(unsigned char return_data[2]);


#endif



