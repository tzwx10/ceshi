#include<reg51.h>
#include<string.h>

#define addr     0x03//从机3的地址
#define _SUCC_   0x0f//数据传送成功
#define _ERR_    0xf0//数据传送失败
unsigned char aa=0xff;//主机与从机之间通信标志
unsigned char Buff[3]={0x01,0x02,0x03};//数据缓冲区
sbit Rs485_die=P3^7; //高电平输出  低电平输入
unsigned char biao;
sbit led=P2^0;

 void delay_1ms(unsigned int t)
{
 unsigned int x,y;
 for(x=t;x>0;x--)
  for(y=110;y>0;y--);
}


//串口初始化函数
void serial_init()
{
 TMOD=0x20; //定时器1工作于方式2
 TH1=0xfd;  
 TL1=0xfd; //波特率为9600
 PCON=0;
 SCON=0xd0;  //串口工作于方式3
 TR1=1;  //开启定时器
 TI=0;
 RI=0;
 
 //ES=1;						//打开接收中断
 //EA=1;						//打开总中断

}



void main()
{
  unsigned char tempt1,i;
  serial_init();
  biao=0;
  SM2=1;   
  Rs485_die=0;
  led=1;
 while(1)
 {
              //接收地址帧
       while(tempt1!=addr)
	   {
			 delay_1ms(300);
	   	   Rs485_die=0;
		   RI=0;
		   while(!RI);
	   	   tempt1=SBUF;
	   
	   
	   }
		led=~led;
	    SM2=0; 

	    TI=0;
		Rs485_die=1;
	    SBUF=addr;
		while(!TI);
		TI=0;

	   	Rs485_die=0;


		
		   RI=0;
		   while(!RI);
	   	   Buff[0]=SBUF;
		   
		   RI=0;
		
	

		 

		 Rs485_die=1;
		 TI=0;
	    SBUF= Buff[0];
		while(!TI);
	 	TI=0;


	    SBUF=Buff[1];
	//	SBUF=0X01;
		while(!TI);
	 	TI=0;

       Rs485_die=0;
	   tempt1=0X00;
	   SM2=1 ;
	


 }
}
		void Usart() interrupt 4
{
    
    if(biao==0) 
	{
	      
         while(!RI);
         aa=SBUF;

		 if(aa==addr)
	   {
	 	  SM2=0;
	   	  biao=1;
		  RI=0;
	   }else
	   {
	   	  RI=0;
	   }	 
	}
	if(biao==1)
	{
	 	while(!RI);
	 	Buff[0]=SBUF;
		aa=0xff;
		
	    SM2=1;
		biao=0;
     	RI=0;
	   
	}   
	 
} 

