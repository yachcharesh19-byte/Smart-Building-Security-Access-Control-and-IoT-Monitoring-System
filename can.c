#include <LPC21xx.H>
#include "header.h"

//CAN INIT
void can1_init(void)
{
	VPBDIV=1;//PCLK=60MHz
	PINSEL1|=0x40000;//P0.25-->RD1
	C1MOD=1;
	C1BTR=0x001C001D;//125Kbps
	AFMR=2;
	C1MOD=0;
}

#define TCS ((C1GSR>>3)&1)
#define RBS (C1GSR&1)

//CAN TX
void can1_tx(CAN1 v)
{
	C1TID1=v.id;
	C1TFI1=v.dlc<<16;
	if(v.rtr==0)
	{
		C1TDA1=v.byteA;
		C1TDB1=v.byteB;
	}
	else
		C1TFI1|=(1<<30);

	C1CMR=0x21;
	while(TCS==0);
}

//CAN RX
void can1_rx(CAN1 *ptr)
{
	while(RBS==0);
	ptr->id=C1RID;
	ptr->dlc=(C1RFS>>16)&0xF;
	ptr->rtr=(C1RFS>>30)&1;
	ptr->ff=(C1RFS>>31)&1;
	if(ptr->rtr==0)
	{
		ptr->byteA=C1RDA;
		ptr->byteB=C1RDB;
	}
	C1CMR=(1<<2);
}

//CAN SEND STATUS
void can1_parameter(u8 t,u8 w,u8 d)
{
	CAN1 MSG;
	MSG.id=0x301;
	MSG.rtr=0;
	MSG.dlc=8;
	MSG.byteA=0;
	MSG.byteA|=t;
	MSG.byteA|=w<<8;
	MSG.byteA|=d<<16;
	can1_tx(MSG);
}
