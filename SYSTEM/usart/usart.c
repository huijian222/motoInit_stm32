#include "usart.h"	
#include "usart2.h"
#include "data_transfer.h"
//#define USART_REC_LEN            200 
//u8 RxBuffer[USART_REC_LEN]; //数组最大为USART_REC_LEN 
//u16 RxState=0;       //结合搜状态标记
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	if(Flag_Show==1)
	{	
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
	USART2->DR = (u8) ch;      
	}
	else
	{	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	}	
	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////
/**************************实现函数**********************************************
*功    能:		usart1发送一个字节
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
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  //使能串口时钟 
	GPIOA->CRH&=0XFFFFF00F;//IO状态设置
	GPIOA->CRH|=0X000008B0;//IO状态设置
		  
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位	   	   
	//波特率设置
 	USART1->BRR=mantissa; // 波特率设置	 
	USART1->CR1|=0X200C;  //1位停止,无校验位.
    USART1->CR1|=1<<8;    //PE中断使能
	USART1->CR1|=1<<5;    //接收缓冲区非空中断使能
    MY_NVIC_Init(1,1,USART1_IRQn,1);//组2，最低优先级 
}

//void PrintString1(unsigned char *puts,unsigned char _cnt)		//发送一串字符串
//{	
//	unsigned char i=0;
//	do{usart1_send(*(puts+i));i=i+1;}while((i)!= _cnt);
//}
///**************************************************************************
//函数功能：串口1接收中断
//入口参数：无
//返回  值：无
//**************************************************************************/
//void USART1_IRQHandler(void) {
//    u8 res;
//    static u8 _data_len = 0,_data_cnt = 0;

//    if(USART1->SR&(1<<5)) {   //接收到数据
//Led_Flash(400);
//        res=USART1->DR;                            
//    }
//    if(RxState==0&&res==0xAA)           //半双工的接受方式在 串口中断中接受 ，但是不能在串口的中，
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
