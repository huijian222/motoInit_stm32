#include "sys.h"
#include "data_transfer.h"
#include "pid.h"
U8 data_to_send_ok=0;
U8 Pwm_Unable = 0;
float target_global = 0;
int Pitch_last = 0;
U8 data_to_send[40],FLAG_RETURN;
/**************************************************************************
函数功能：解析上位机发下来指令
入口参数：无
返回  值：无
作    者：赖金榜
**************************************************************************/
void Data_Receive_Anl(U8 *data_buf,U8 num) {
//	S16 rc_value_temp;
	U8 sum = 0,i=0;
	for( i=0;i<(num-1);i++)sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;		//??sum
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		return;		//????
/////////////////////////////////////////////////////////////////////////////////////
	if(*(data_buf+2)==0X01)
	{
		if(*(data_buf+4)==0X01);
		if(*(data_buf+4)==0X02);
		if(*(data_buf+4)==0X03);
		if(*(data_buf+2)==0X02)
		{
			if(*(data_buf+4)==0X01)
			{
	//			Send_PID1 = 1;
	//			Send_PID2 = 1;
	//			Send_PID3 = 1;
	//			Send_PID4 = 1;
	//			Send_PID5 = 1;
	//			Send_PID6 = 1;
			}
			if(*(data_buf+4)==0X02);
	//			Send_Offset = 1;
		}
	}
	if(*(data_buf+2)==0X12)								//PID3
	{
        PID_PID_2.Kp = (float)((int)(*(data_buf+4)<<8)|*(data_buf+5))/100;
        PID_PID_2.Ki = (float)((int)(*(data_buf+6)<<8)|*(data_buf+7))/10000;
        PID_PID_2.Kd = (float)((int)(*(data_buf+8)<<8)|*(data_buf+9))/1000;
//   	target_global = (float)((S16)(*(data_buf+10)<<8)|*(data_buf+11))/100;
//		PID_PID_3.I = (float)((S16)(*(data_buf+12)<<8)|*(data_buf+13))/100;
//   	PID_PID_3.D = (float)((S16)(*(data_buf+14)<<8)|*(data_buf+15))/100;
//		PID_PID_4.P = (float)((S16)(*(data_buf+16)<<8)|*(data_buf+17))/100;
//		PID_PID_4.I = (float)((S16)(*(data_buf+18)<<8)|*(data_buf+19))/100;
//		PID_PID_4.D = (float)((S16)(*(data_buf+20)<<8)|*(data_buf+21))/100;
//      Data_Send_Check(sum);
	}
	if(*(data_buf+2)==0X13)								//PID4
	{
//			PID_PID_5.P = (float)((vs16)(*(data_buf+4)<<8)|*(data_buf+5))/100;
//			PID_PID_5.I = (float)((vs16)(*(data_buf+6)<<8)|*(data_buf+7))/100;
//			PID_PID_5.D = (float)((vs16)(*(data_buf+8)<<8)|*(data_buf+9))/100;
//			PID_PID_6.P = (float)((vs16)(*(data_buf+10)<<8)|*(data_buf+11))/100;
//			PID_PID_6.I = (float)((vs16)(*(data_buf+12)<<8)|*(data_buf+13))/100;
//			PID_PID_6.D = (float)((vs16)(*(data_buf+14)<<8)|*(data_buf+15))/100;
//			PID_PID_7.P = (float)((vs16)(*(data_buf+16)<<8)|*(data_buf+17))/100;
//			PID_PID_7.I = (float)((vs16)(*(data_buf+18)<<8)|*(data_buf+19))/100;
//			PID_PID_7.D = (float)((vs16)(*(data_buf+20)<<8)|*(data_buf+21))/100;
//			Data_Send_Check(sum);
	}
	if(*(data_buf+2)==0X14)								//PID5
	{
//			PID_PID_8.P = (float)((vs16)(*(data_buf+4)<<8)|*(data_buf+5))/100;
//			PID_PID_8.I = (float)((vs16)(*(data_buf+6)<<8)|*(data_buf+7))/100;
//			PID_PID_8.D = (float)((vs16)(*(data_buf+8)<<8)|*(data_buf+9))/100;
//			PID_PID_9.P = (float)((vs16)(*(data_buf+10)<<8)|*(data_buf+11))/100;
//			PID_PID_9.I = (float)((vs16)(*(data_buf+12)<<8)|*(data_buf+13))/100;
//			PID_PID_9.D = (float)((vs16)(*(data_buf+14)<<8)|*(data_buf+15))/100;
//			PID_PID_10.P = (float)((vs16)(*(data_buf+16)<<8)|*(data_buf+17))/100;
//			PID_PID_10.I = (float)((vs16)(*(data_buf+18)<<8)|*(data_buf+19))/100;
//			PID_PID_10.D = (float)((vs16)(*(data_buf+20)<<8)|*(data_buf+21))/100;
//			Data_Send_Check(sum);
	}
	if(*(data_buf+2)==0X15)								//PID6
	{
//			PID_PID_11.P = (float)((vs16)(*(data_buf+4)<<8)|*(data_buf+5))/100;
//			PID_PID_11.I = (float)((vs16)(*(data_buf+6)<<8)|*(data_buf+7))/100;
//			PID_PID_11.D = (float)((vs16)(*(data_buf+8)<<8)|*(data_buf+9))/100;
//			PID_PID_12.P = (float)((vs16)(*(data_buf+10)<<8)|*(data_buf+11))/100;
//			PID_PID_12.I = (float)((vs16)(*(data_buf+12)<<8)|*(data_buf+13))/100;
//			PID_PID_12.D = (float)((vs16)(*(data_buf+14)<<8)|*(data_buf+15))/100;
//			Data_Send_Check(sum);
//			EE_SAVE_PID();
	}
	if(*(data_buf+2)==0X16)								//OFFSET
	{
//			AngleOffset_Rol = (float)((vs16)(*(data_buf+4)<<8)|*(data_buf+5))/1000;
//			AngleOffset_Pit = (float)((vs16)(*(data_buf+6)<<8)|*(data_buf+7))/1000;
	}
			if(*(data_buf+2)==0X02)								//OFFSET
	{
//			AngleOffset_Rol = (float)((vs16)(*(data_buf+4)<<8)|*(data_buf+5))/1000;
//			AngleOffset_Pit = (float)((vs16)(*(data_buf+6)<<8)|*(data_buf+7))/1000;
        /******************************************
        此处当指令为0x02时 在主循环中调用 
        void Data_Send_PID2(void)
        向上位机发送 PID2 数据
                                                    */
			FLAG_RETURN = 1;
	}
	Data_Send_Check(sum);
}
/**************************************************************************
函数功能：向匿名上位机发送 FLOAT 变量 在上位机绘制出关于变量的波形 以便观察 PWM 和 PID 之间的变化 方便调参
入口参数：四个 FLOAT 型变量 
返回  值：无
作    者：赖金榜
**************************************************************************/
void Data_Send_Senser(float sv,float pv,float tv, float av) {
	U8 _cnt=0,i=0,sum=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xF1;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=BYTE3(sv);  //?8?
	data_to_send[_cnt++]=BYTE2(sv);  //?8?
	data_to_send[_cnt++]=BYTE1(sv);  //?8?
	data_to_send[_cnt++]=BYTE0(sv);  //?8?
	data_to_send[_cnt++]=BYTE3(pv);  //?8?
	data_to_send[_cnt++]=BYTE2(pv);  //?8?
	data_to_send[_cnt++]=BYTE1(pv);  //?8?
	data_to_send[_cnt++]=BYTE0(pv);  //?8?
	data_to_send[_cnt++]=BYTE3(tv);  //?8?
	data_to_send[_cnt++]=BYTE2(tv);  //?8?
	data_to_send[_cnt++]=BYTE1(tv);  //?8?
	data_to_send[_cnt++]=BYTE0(tv);  //?8?
    data_to_send[_cnt++]=BYTE3(av);  //?8?
	data_to_send[_cnt++]=BYTE2(av);  //?8?
	data_to_send[_cnt++]=BYTE1(av);  //?8?
	data_to_send[_cnt++]=BYTE0(av);  //?8?
	data_to_send[3] = _cnt-4;
	for( i=0;i<_cnt;i++)sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	PrintString1(data_to_send,_cnt);
}
/**************************************************************************
函数功能：向匿名上位机发送 MPU6050 数据 在此次四轴飞行器中暂时没用
入口参数：无
返回  值：无
作    者：赖金榜
**************************************************************************/
void Data_Send_Mpu6050(void)
{
	u8 _cnt=0;
    u8 sum = 0,i= 0;
    Roll = (int)(Roll*100);
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;//BYTE1(Pitch);  //?8?
	data_to_send[_cnt++]=1;//BYTE0(Pitch);  //?8?
	data_to_send[_cnt++]=0;//BYTE1(Roll);
	data_to_send[_cnt++]=2;//BYTE0(Roll);
	data_to_send[_cnt++]=0;//BYTE1(Acc.Z);
	data_to_send[_cnt++]=3;//BYTE0(Acc.Z);
	data_to_send[_cnt++]=0;//BYTE1(Gyr.X);
	data_to_send[_cnt++]=4;//BYTE0(Gyr.X);
	data_to_send[_cnt++]=0;//BYTE1(Gyr.Y);
	data_to_send[_cnt++]=5;//BYTE0(Gyr.Y);
	data_to_send[_cnt++]=0;//BYTE1(Gyr.Z);
	data_to_send[_cnt++]=6;//BYTE0(Gyr.Z);
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=0;
	
	data_to_send[3] = _cnt-4;
	for(;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	PrintString1(data_to_send,_cnt);
}
/**************************************************************************
函数功能：向匿名上位机发送 MPU6050 数据 发送了 俯仰角 航向角 滚转角
入口参数：无
返回  值：无
作    者：赖金榜
**************************************************************************/
void Data_Send_Status(void) {
	u8 _cnt=0;
    u8 i=0;
    vs16 _temp;	
    u8 sum = 0;
	vs32 _temp2 =0;// Alt;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;
	_temp = (int)(Roll*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(Pitch*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	//_temp = (int)(Q_ANGLE.YAW*100);
	_temp = (int)(yaw*100);//(Mag_Heading*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0;//Alt_CSB;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);
	//if(Rc_C.ARMED==0)		
    //data_to_send[_cnt++]=0xA0;	
	//else if(Rc_C.ARMED==1)		
    data_to_send[_cnt++]=0xA1;
	data_to_send[3] = _cnt-4;
	for(;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	PrintString1(data_to_send,_cnt);
}

/**************************************************************************
函数功能：向匿名上位机发送 PID 数据
入口参数：无
返回  值：无
作    者：赖金榜
**************************************************************************/
void Data_Send_PID2(void) {
	unsigned char _cnt=0;
	unsigned int _temp;
	unsigned char sum = 0;  //此处BYTE1 与 BYTE0 颠倒是因为在STM32中编译器的问题 同上函数 
	unsigned char i = 0;    //C51中 无此问题
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x12;
	data_to_send[_cnt++]=0;
	_temp = PID_PID_2.Kp * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = PID_PID_2.Ki * 10000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = PID_PID_2.Kd * 1000;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = target_global* 100 ;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0 * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0 * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0 * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = 0 * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp =0 * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	data_to_send[3] = _cnt-4;
	for(;i<_cnt;i++)
	sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	PrintString1(data_to_send,_cnt);
}
/**************************************************************************
函数功能：向匿名上位机发送 校验位
入口参数：无
返回  值：无
作    者：赖金榜
**************************************************************************/
void Data_Send_Check(U8 check) {
	U8 sum=0 ,i= 0;
	data_to_send[0]=0xAA;
	data_to_send[1]=0xAA;
	data_to_send[2]=0xF0;
	data_to_send[3]=3;
    data_to_send[4]=0xBA;
	data_to_send[5]=00;	
	data_to_send[6]=check;//BYTE0(check);
	for( i=0;i<7;i++)
		sum += data_to_send[i];
	data_to_send[7]=sum;
    data_to_send_ok=1;
}
/**************************************************************************
函数功能：向匿名上位机发送  所有数据  如果不需要发送某样数据 直接在此函数 注释掉 即可
入口参数：四个 FLOAT 型变量 
返回  值：无
作    者：赖金榜
**************************************************************************/
void send_Data_To_Host(float sv,float pv,float tv, float av) {
    Data_Send_Status();
    Data_Send_Senser(sv, pv, tv,  av);
    //Data_Send_Mpu6050();
    if(FLAG_RETURN == 1) {
        Data_Send_PID2();
        FLAG_RETURN = 0;
    }
    if(data_to_send_ok){
        data_to_send_ok=0;																    
        PrintString1(data_to_send,8);
    }
    delay_ms(10);
}
