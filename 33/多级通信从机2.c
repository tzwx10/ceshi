#include<reg51.h>
#include<string.h>

#define addr     0x03//�ӻ�3�ĵ�ַ
#define _SUCC_   0x0f//���ݴ��ͳɹ�
#define _ERR_    0xf0//���ݴ���ʧ��
unsigned char aa=0xff;//������ӻ�֮��ͨ�ű�־
unsigned char Buff[3]={0x01,0x02,0x03};//���ݻ�����
sbit Rs485_die=P3^7; //�ߵ�ƽ���  �͵�ƽ����
unsigned char biao;
sbit led=P2^0;

 void delay_1ms(unsigned int t)
{
 unsigned int x,y;
 for(x=t;x>0;x--)
  for(y=110;y>0;y--);
}


//���ڳ�ʼ������
void serial_init()
{
 TMOD=0x20; //��ʱ��1�����ڷ�ʽ2
 TH1=0xfd;  
 TL1=0xfd; //������Ϊ9600
 PCON=0;
 SCON=0xd0;  //���ڹ����ڷ�ʽ3
 TR1=1;  //������ʱ��
 TI=0;
 RI=0;
 
 //ES=1;						//�򿪽����ж�
 //EA=1;						//�����ж�

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
              //���յ�ַ֡
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

