
#include "usart2.h"
#include "data_transfer.h"
#define USART_REC_LEN            200 
u8 RxBuffer[USART_REC_LEN]; //�������ΪUSART_REC_LEN 
u16 RxState=0;       //�����״̬���
/**************************************************************************
�������ܣ�����2��ʼ��
��ڲ�����pclk2:PCLK2 ʱ��Ƶ��(Mhz)    bound:������
����  ֵ����
**************************************************************************/
void uart2_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB1ENR|=1<<17;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRL&=0XFFFF00FF; 
	GPIOA->CRL|=0X00008B00;//IO״̬����
	GPIOA->ODR|=1<<2;	  
	RCC->APB1RSTR|=1<<17;   //��λ����1
	RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ	   	   
	//����������
 	USART2->BRR=mantissa; // ����������	 
	USART2->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж�
	USART2->CR1|=1<<8;    //PE�ж�ʹ��
	USART2->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(3,3,USART2_IRQn,2);//��2��������ȼ� 
}
void usart2_send(u8 data)
{
	USART2->DR = data;
	while((USART2->SR&0x40)==0);	
}
void PrintString1(unsigned char *puts,unsigned char _cnt)		//����һ���ַ���
{	
	unsigned char i=0;
	do{usart2_send(*(puts+i));i=i+1;}while((i)!= _cnt);
}
/**************************************************************************
�������ܣ�����2�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART2_IRQHandler(void) {
    u8 res;
    static u8 _data_len = 0,_data_cnt = 0;

    if(USART2->SR&(1<<5)) {   //���յ�����
        res=USART2->DR;                            
    }
    if(RxState==0&&res==0xAA)           //��˫���Ľ��ܷ�ʽ�� �����ж��н��� �����ǲ����ڴ��ڵ��У�
    {
        
        RxState=1;
        RxBuffer[0]=res;				
    }
    else if(RxState==1&&res==0xAF)
    {
        
        RxState=2;
        RxBuffer[1]=res;
    }
    else if(RxState==2&&res>0&&res<0XF1)
    {
        
        RxState=3;
        RxBuffer[2]=res;
        
    }
    else if(RxState==3&&res<50)
    {
        RxState=4;
        RxBuffer[3]=res;
        _data_len = res;
        _data_cnt = 0;
    }
    else if(RxState==4&&_data_len>0)
    {
        _data_len--;
        RxBuffer[4+_data_cnt++]=res;
        if(_data_len==0)
        RxState = 5;								
    }
    else if(RxState==5)
    {
        RxState = 0;
        RxBuffer[4+_data_cnt]=res;
        Data_Receive_Anl(RxBuffer,_data_cnt+5);
       						
    }
    else
    {RxState = 0; }				
}
