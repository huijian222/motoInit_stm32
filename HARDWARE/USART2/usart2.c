
#include "usart2.h"
#include "data_transfer.h"
#define USART_REC_LEN            200 
u8 RxBuffer[USART_REC_LEN]; //数组最大为USART_REC_LEN 
u16 RxState=0;       //结合搜状态标记
/**************************************************************************
函数功能：串口2初始化
入口参数：pclk2:PCLK2 时钟频率(Mhz)    bound:波特率
返回  值：无
**************************************************************************/
void uart2_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB1ENR|=1<<17;  //使能串口时钟 
	GPIOA->CRL&=0XFFFF00FF; 
	GPIOA->CRL|=0X00008B00;//IO状态设置
	GPIOA->ODR|=1<<2;	  
	RCC->APB1RSTR|=1<<17;   //复位串口1
	RCC->APB1RSTR&=~(1<<17);//停止复位	   	   
	//波特率设置
 	USART2->BRR=mantissa; // 波特率设置	 
	USART2->CR1|=0X200C;  //1位停止,无校验位.
	//使能接收中断
	USART2->CR1|=1<<8;    //PE中断使能
	USART2->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART2_IRQn,2);//组2，最低优先级 
}
void usart2_send(u8 data)
{
	USART2->DR = data;
	while((USART2->SR&0x40)==0);	
}
void PrintString1(unsigned char *puts,unsigned char _cnt)		//发送一串字符串
{	
	unsigned char i=0;
	do{usart2_send(*(puts+i));i=i+1;}while((i)!= _cnt);
}
/**************************************************************************
函数功能：串口2接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART2_IRQHandler(void) {
    u8 res;
    static u8 _data_len = 0,_data_cnt = 0;

    if(USART2->SR&(1<<5)) {   //接收到数据
        res=USART2->DR;                            
    }
    if(RxState==0&&res==0xAA)           //半双工的接受方式在 串口中断中接受 ，但是不能在串口的中，
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
