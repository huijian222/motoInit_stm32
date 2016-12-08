#include "pid.h"
PID PID_PID_2;
/**************************************************************************
函数功能：PID 初始化
入口参数：无
返回值：无
作    者：赖金榜
**************************************************************************/
void PID_init(void){
    PID_PID_2.SetSpeed=0.0;
    PID_PID_2.ActualSpeed=0.0;		//
    PID_PID_2.err=0.0;
    PID_PID_2.err_last=0.0;
    PID_PID_2.voltage=0.0;
    PID_PID_2.integral=0.0;
    PID_PID_2.Kp=1.1;   //200 p:0.07jike 
    PID_PID_2.Ki=0.07;
    PID_PID_2.Kd=0.0;
}
/**************************************************************************
函数功能：进行 pid 运算 比较设定 speed 值和实际的速度值的差值 进行 pid 运算
入口参数：float speed  float actual
返回  值PID_PID_2.ActualSpeed
作    者：赖金榜
**************************************************************************/
float PID_realize(float speed ,float actual){
	PID_PID_2.ActualSpeed=actual;	   //MaxActual 在pid.h中定义
    PID_PID_2.SetSpeed=speed;
    PID_PID_2.err=PID_PID_2.SetSpeed-PID_PID_2.ActualSpeed;
    if(PID_PID_2.Ki != 0)PID_PID_2.integral += PID_PID_2.err;
	if(PID_PID_2.integral > 100) PID_PID_2.integral = 100;
	if(PID_PID_2.integral < -100) PID_PID_2.integral = -100;
    PID_PID_2.voltage=PID_PID_2.Kp*PID_PID_2.err+PID_PID_2.Ki*PID_PID_2.integral+PID_PID_2.Kd*(PID_PID_2.err-PID_PID_2.err_last);
    PID_PID_2.err_last=PID_PID_2.err;
    PID_PID_2.ActualSpeed=PID_PID_2.voltage*1.0;
    return  PID_PID_2.ActualSpeed;
}
/**************************************************************************
函数功能：调用 PID_realize 来运算 PID 
入口参数：float target float adc
返回  值：float PID_num
作    者：赖金榜
**************************************************************************/
float PID_application(float target,float adc){
	float PID_num;
	PID_num = PID_realize(target,adc);//(target, (float)((adc_P0_0-640)/360) );
	if(PID_num > 1){
		PID_num = 1.0;
	}
	if(PID_num < -0){
		PID_num = 0;
	}
//	PID_num=(PID_num+1.0)/2.0;
	return PID_num;
}
