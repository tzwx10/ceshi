#include<reg51.h>
#include<string.h>

#define _SUCC_   0x0f//���ݴ��ͳɹ�
#define _ERR_    0xf0//���ݴ���ʧ��
#define u8 unsigned char

unsigned char Table[9]={0x01,0x02,0x04,0x08,0x35,0x36,0x37,0x38,0x39};	//ǰ3���ֽ�Ϊ�ٶ�  �������ֽ�Ϊ�����ٶ� ��ѹ��ֵ
//unsigned char Table[]="123456789";
unsigned char Buff[3]={0x08,0X05,0X03};  //���ݻ�����
unsigned char temp=0xff;
sbit KEY1=P2^1;
sbit KEY2=P2^2;
sbit KEY3=P2^3;
sbit led=P2^0;

sbit LED1=P2^4;
sbit LED2=P2^5;
sbit LED3=P2^6;
sbit Rs485_die=P3^7; //�ߵ�ƽ���  �͵�ƽ����
u8 tempt1;
//unsigned char addr;

//��ʱ1ms����
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
  TB8=1;SM2=0; Rs485_die=1;	 //fa song di zi	���͵�ַ
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


void delay_1ms(unsigned int t)//��ʱ
{
 unsigned int x,y;
 for(x=t;x>0;x--)
  for(y=110;y>0;y--);
}
//��������ʼ��
 

//���ڳ�ʼ������
void serial_init(void)
{
 TMOD=0x20; //��ʱ��1�����ڷ�ʽ2
 TH1=0xfd;  
 TL1=0xfd; //������Ϊ9600
 PCON=0;
 SCON=0xd0;  //���ڹ����ڷ�ʽ3
 TR1=1;  //������ʱ��
 TI=0;	//							   ����жϱ�־λ
 RI=0;
 //ES=1;						//�򿪽����ж�
 //EA=1;						//�����ж�
 SM2=0;
}
//�������ݺ���
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
 