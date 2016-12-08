#include "sys.h"
#include "control.h"	
#include "data_transfer.h"
#include "pid.h"


u8 Way_Angle=1;                             //��ȡ�Ƕȵ��㷨��1:DMP2�������� ���Ըĳ�3 �������˲���
u8 Flag_Show=1,Flag_Stop=1;                 //��ʾ��־λ ��ͣ��־λ
int Temperature;                            //��ʾ�¶�
int Moto1,Moto2,Moto3,Moto4;               //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int main(void) { 
    
	Stm32_Clock_Init(9);            //ϵͳʱ������
	delay_init(72);                 //��ʱ��ʼ�� 
	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
	LED_Init();                     //��ʼ���� LED ���ӵ�Ӳ���ӿ�
	KEY_Init();                     //������ʼ��
	OLED_Init();                    //OLED��ʼ��
//	uart_init(72,115200);           //��ʼ������1
    uart2_init(36,115200);            //����2��ʼ��
	MiniBalance_PWM_Init(1999,144);   //=====��ʼ��PWM 10KHZ������������� �����ʼ������ӿ� ��ΪMiniBalance_PWM_Init(9999,35) 200HZ �޸ĵ�50HZ 
    initMoto();
    IIC_Init();                     //ģ��IIC��ʼ��
    MPU6050_initialize();           //=====MPU6050��ʼ��	
	DMP_Init();                     //��ʼ��DMP     
    PID_init();
//    Timer1_Init(49,7199);           //=====5MS��һ���жϷ�����
	while(1) {  
//        
     	if(Way_Angle==1) {                    //DMPû���漰���ϸ��ʱ�����⣬����������ȡ
               
            Read_DMP();                      //===��ȡ���ٶȺ����
        }  
        if(Flag_Stop==1) {//ʹ��OLED��ʾ����PC�˴��ڵ�������

            Way_Angle=1;//ʹ��DMP
            Temperature=Read_Temperature();  //===��ȡMPU6050�����¶ȴ��������ݣ����Ʊ�ʾ�����¶ȡ�	
            oled_show(); //===��ʾ����
            send_Data_To_Host((float)Pwm_Unable,(float)Moto2,(float)Moto3,(float)Moto4);
//            printf("X�����%f  Y�����%f   \r\n",Pitch,Roll);
            delay_ms(10);
        }	
	} 
}



