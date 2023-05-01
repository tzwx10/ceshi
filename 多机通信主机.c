#include<reg51.h>
#include<string.h>

#define _SUCC_   0x0f//数据传送成功
#define _ERR_    0xf0//数据传送失败
#define u8 unsigned char

unsigned char Table[9]={0x01,0x02,0x04,0x08,0x35,0x36,0x37,0x38,0x39};	//前3个字节为速度  后六个字节为返回速度 和压力值
//unsigned char Table[]="123456789";
unsigned char Buff[3]={0x08,0X05,0X03};  //数据缓冲区
unsigned char temp=0xff;
sbit KEY1=P2^1;
sbit KEY2=P2^2;
sbit KEY3=P2^3;
sbit led=P2^0;

sbit LED1=P2^4;
sbit LED2=P2^5;
sbit LED3=P2^6;
sbit Rs485_die=P3^7; //高电平输出  低电平输入
u8 tempt1;
//unsigned char addr;

//延时1ms函数
 void delay_1ms(unsigned int t);

 void serial_init(void);
 u8 SEND_data(u8 addr,u8 *Buff);
     
void main()
{
 

 serial_init();
  KEY1=1;
  KEY2=1;
  KEY3=1;
  Rs485_die=1;
  TB8=1;SM2=0; Rs485_die=1;	 //fa song di zi	发送地址
  led=1;
 while(1)
 {
   
   TB8=1;
	if(KEY1==0)
  {
		delay_1ms(5);
		if(KEY1==0)
		{
   	 
			SEND_data(0x01,Buff);
			delay_1ms(300);
			LED1=~LED1;
	    delay_1ms(30);
		}
  }
 
	if(KEY2==0)
	{
		delay_1ms(5);
		if(KEY2==0)
		{
			delay_1ms(300);
			LED2=~LED2;
			SEND_data(0x02,Buff);
	
	
		}
	}


	if(KEY3==0)
  {
		delay_1ms(5);
		if(KEY3==0)
		{
			
  
			delay_1ms(300);
			LED3=~LED3;
			SEND_data(0x03,Buff);
	
	
		}
	}

  





 }
}


void delay_1ms(unsigned int t)//延时
{
 unsigned int x,y;
 for(x=t;x>0;x--)
  for(y=110;y>0;y--);
}
//缓冲区初始化
 

//串口初始化函数
void serial_init(void)
{
 TMOD=0x20; //定时器1工作于方式2
 TH1=0xfd;  
 TL1=0xfd; //波特率为9600
 PCON=0;
 SCON=0xd0;  //串口工作于方式3
 TR1=1;  //开启定时器
 TI=0;	//							   清除中断标志位
 RI=0;
 //ES=1;						//打开接收中断
 //EA=1;						//打开总中断
 SM2=0;
}
//发送数据函数
u8 SEND_data(u8 addr,u8 *Buff)
{
      u8 i=0;
	 
      Rs485_die=1;
      TB8=1;
	  TI=0;
	  SBUF=addr;
	  while(!TI);
	  TI=0;
	    
	  Rs485_die=0;
	  RI=0;
	  while(!RI);
	  tempt1 =SBUF;
	  RI=0;
	   if(tempt1==addr)
	   {
	   		led=0;
	   		TB8=0;
	   } else
	   {
	   	  return 0;
	   }

	    Rs485_die=1;
		 TI=0;
		 SBUF=Buff[0];
		 while(!TI);
		 TI=0;


		Rs485_die=0;
	    RI=0;
		while(!RI);
		tempt1=SBUF;
		if(tempt1==addr)led=1;
		RI=0;

	
		while(!RI);				  
		Buff[1]=SBUF;
		if(Buff[1]==addr)led=1;
		 RI=0;

		Rs485_die=1;



}
 