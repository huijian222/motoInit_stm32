#include "usart.h"	
#include "usart2.h"
#include "data_transfer.h"
//#define USART_REC_LEN            200 
//u8 RxBuffer[USART_REC_LEN]; //�������ΪUSART_REC_LEN 
//u16 RxState=0;       //�����״̬���
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	if(Flag_Show==1)
	{	
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
	USART2->DR = (u8) ch;      
	}
	else
	{	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	}	
	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////
/**************************ʵ�ֺ���**********************************************
*��    ��:		usart1����һ���ֽ�
*********************************************************************************/
void usart1_send(u8 data)
{
	USART1->DR = data;
	while((USART1->SR&0x40)==0);	
}
void uart_init(u32 pclk2,u32 bound)
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
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
	GPIOA->CRH|=0X000008B0;//IO״̬����
		  
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
    USART1->CR1|=1<<8;    //PE�ж�ʹ��
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��
    MY_NVIC_Init(1,1,USART1_IRQn,1);//��2��������ȼ� 
}

//void PrintString1(unsigned char *puts,unsigned char _cnt)		//����һ���ַ���
//{	
//	unsigned char i=0;
//	do{usart1_send(*(puts+i));i=i+1;}while((i)!= _cnt);
//}
///**************************************************************************
//�������ܣ�����1�����ж�
//��ڲ�������
//����  ֵ����
//**************************************************************************/
//void USART1_IRQHandler(void) {
//    u8 res;
//    static u8 _data_len = 0,_data_cnt = 0;

//    if(USART1->SR&(1<<5)) {   //���յ�����
//Led_Flash(400);
//        res=USART1->DR;                            
//    }
//    if(RxState==0&&res==0xAA)           //��˫���Ľ��ܷ�ʽ�� �����ж��н��� �����ǲ����ڴ��ڵ��У�
//    {
//        
//        RxState=1;
//        RxBuffer[0]=res;				
//    }
//    else if(RxState==1&&res==0xAF)
//    {
//        
//        RxState=2;
//        RxBuffer[1]=res;
//    }
//    else if(RxState==2&&res>0&&res<0XF1)
//    {
//        
//        RxState=3;
//        RxBuffer[2]=res;
//        
//    }
//    else if(RxState==3&&res<50)
//    {
//        RxState=4;
//        RxBuffer[3]=res;
//        _data_len = res;
//        _data_cnt = 0;
//    }
//    else if(RxState==4&&_data_len>0)
//    {
//        _data_len--;
//        RxBuffer[4+_data_cnt++]=res;
//        if(_data_len==0)
//        RxState = 5;								
//    }
//    else if(RxState==5)
//    {
//        RxState = 0;
//        RxBuffer[4+_data_cnt]=res;
//        Data_Receive_Anl(RxBuffer,_data_cnt+5);
//       						
//    }
//    else
//    {RxState = 0; }				
//}
