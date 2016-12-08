#include "sys.h"
#include "control.h"	
#include "data_transfer.h"
#include "pid.h"


u8 Way_Angle=1;                             //获取角度的算法，1:DMP2：卡尔曼 可以改成3 即互补滤波，
u8 Flag_Show=1,Flag_Stop=1;                 //显示标志位 启停标志位
int Temperature;                            //显示温度
int Moto1,Moto2,Moto3,Moto4;               //电机PWM变量 应是Motor的 向Moto致敬	
int main(void) { 
    
	Stm32_Clock_Init(9);            //系统时钟设置
	delay_init(72);                 //延时初始化 
	JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
	LED_Init();                     //初始化与 LED 连接的硬件接口
	KEY_Init();                     //按键初始化
	OLED_Init();                    //OLED初始化
//	uart_init(72,115200);           //初始化串口1
    uart2_init(36,115200);            //串口2初始化
	MiniBalance_PWM_Init(1999,144);   //=====初始化PWM 10KHZ，用于驱动电机 如需初始化电调接口 改为MiniBalance_PWM_Init(9999,35) 200HZ 修改到50HZ 
    initMoto();
    IIC_Init();                     //模拟IIC初始化
    MPU6050_initialize();           //=====MPU6050初始化	
	DMP_Init();                     //初始化DMP     
    PID_init();
//    Timer1_Init(49,7199);           //=====5MS进一次中断服务函数
	while(1) {  
//        
     	if(Way_Angle==1) {                    //DMP没有涉及到严格的时序问题，在主函数读取
               
            Read_DMP();                      //===读取角速度和倾角
        }  
        if(Flag_Stop==1) {//使用OLED显示屏和PC端串口调试助手

            Way_Angle=1;//使用DMP
            Temperature=Read_Temperature();  //===读取MPU6050内置温度传感器数据，近似表示主板温度。	
            oled_show(); //===显示屏打开
            send_Data_To_Host((float)Pwm_Unable,(float)Moto2,(float)Moto3,(float)Moto4);
//            printf("X轴倾角%f  Y轴倾角%f   \r\n",Pitch,Roll);
            delay_ms(10);
        }	
	} 
}



